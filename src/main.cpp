/** @file main.cpp
 *  @brief Main functions
 *
 *  Contains all the main functions of the pll simulator.
 *
 *  @author Americo Dias
 *  @date 06/02/2018
 */
/** @cond */
#include <iostream>
#include <fstream>
#include "include/json.hpp"
#include "include/cxxopts.hpp"
#include "systemc.h"
#include "systemc-ams.h"
/** @endcond */
#include "sc_pll.h"


#define VERSION "1.0"
#define NAME "SystemC-AMS PLL simulator"
#define concat(first, second, thirt) first second thirt

using namespace std;
using json = nlohmann::json;

/**
 * Read json options from a file
 * @param filename: Filename of the file containing the options in json format
 * @return json: JSON object containing the parsed options
 */
json get_options(string filename) {
	json j;

	// read a JSON file
	try {
		std::ifstream i(filename);
		i >> j;
	}
	catch (json::exception& e)
	{
		// output exception information
		std::cout << "message: " << e.what() << '\n'
				<< "exception id: " << e.id << std::endl;
	}
	catch (int e)
	{
		cout << "An exception occurred. Exception Nr. " << e << '\n';
	}

	return j;
}

/**
 * Parse the command line arguments
 * @param argc Number of command line arguments
 * @param argv Command line arguments
 * @return Configuration filename, Output format
 */
std::pair<string, string> parse_opt(int argc, char* argv[]) {
	string format;
	string config_filename;

	try
	{
		const char* header = concat(NAME, " ", VERSION);
		cxxopts::Options opt(argv[0], header);
		opt.positional_help("[optional args]").show_positional_help();

		opt.add_options()
				("c,config", "Configuration file", cxxopts::value<std::string>()->default_value("options.json"))
				("f,format", "Output file format (vcd or csv)", cxxopts::value<std::string>()->default_value("vcd"))
				("h,help", "Print help");

		auto result = opt.parse(argc, argv);

		if (result["help"].as<bool>())
		{
		      std::cout << opt.help() << std::endl;
		      exit(0);
		}

		config_filename = result["config"].as<std::string>();
		format = result["format"].as<std::string>();

		ifstream infile(config_filename);

		if(!infile.good()) {
			cout << "The configuration file is missing!" << endl;
			exit(-1);
		}

		if(format.compare("vcd") != 0 && format.compare("csv") != 0) {
			cout << "Invalid output format!" << endl;
			exit(-1);
		}

	} catch (const cxxopts::OptionException& e)
	{
		std::cout << "error parsing options: " << e.what() << std::endl;
		exit(-1);
	}

	return std::make_pair(config_filename, format);
}

/**
 * Main function
 * @param argc Number of command line arguments
 * @param argv Command line arguments
 * @return int: Status
 */
int sc_main(int argc, char* argv[]){

	json options;					// JSON options
	string format;					// Output format: vcd, csv
	string config_filename;			// Configuration filename

	cout << endl << endl;
	std::tie(config_filename,format) = parse_opt(argc, argv);	// Parse command line arguments
	options = get_options(config_filename);						// Parse json options file


	// Top level signals:
	sc_clock sc_sig_fref ("sig_fref",										// Reference clock
							sc_time(1/(double)options["system"]["fref"],
							sc_core::SC_SEC), 0.5,
							sc_time(0.5/(double)options["system"]["fref"],
							sc_core::SC_SEC));
	sca_tdf::sca_signal<double> sca_tdf_sig_fout_freq;						// Output frequency

	// Declaration of the pll block:
	sc_pll	pll("pll",
			(double)options["phase_detector"]["tr"],
			(double)options["phase_detector"]["tf"],
			(double)options["system"]["tstep"],
			(double)options["system"]["vdd"],
			(double)options["charge_pump"]["current_up"],
			(double)options["charge_pump"]["current_dn"],
			(double)options["charge_pump"]["current_leak"],
			(double)options["charge_pump"]["mosfet_vth"],
			   (int)options["loop_filter"]["order"],
			(double)options["loop_filter"]["r1"],
			(double)options["loop_filter"]["c1"],
			(double)options["loop_filter"]["c2"],
			(double)options["loop_filter"]["r3"],
			(double)options["loop_filter"]["c3"],
			(double)options["system"]["vcm"],
			(double)options["vco"]["kvo"],
			(double)options["vco"]["fmin"],
			(double)options["divider"]["n"] );

	// Bind the top level signals:
	pll.sc_in_fref->bind(sc_sig_fref);
	pll.sca_tdf_out_fout_freq->bind(sca_tdf_sig_fout_freq);

	// Print some useful information:
	cout << "Info: Simulation options:" << endl;
	cout << "         Simulation time:     " << (double)options["system"]["tsim"] << endl;
	cout << "         Simulation timestep: " << (double)options["system"]["tstep"] << endl;
	cout << "         Ouput format:        " << format << endl;

	// Trace signals
	sca_trace_file* tr;

	if(format.compare("vcd") == 0)
		tr = sca_create_vcd_trace_file("output"); // Usual SystemC tracing
	else
		tr = sca_create_tabular_trace_file("output"); // Usual SystemC tracing

	sca_trace(tr, sc_sig_fref ,"sc_sig_fref");
	sca_trace(tr, sca_tdf_sig_fout_freq ,"sca_tdf_sig_fout_freq");
	sca_trace(tr, pll.sc_sig_up ,"pll.sc_sig_up");
	sca_trace(tr, pll.sc_sig_dn ,"pll.sc_sig_dn");
	sca_trace(tr, pll.sc_sig_fdiv ,"pll.sc_sig_fdiv");
	sca_trace(tr, pll.sca_tdf_sig_vctrl ,"pll.sca_tdf_sig_vctrl");
	sca_trace(tr, pll.sca_tdf_sig_ictrl ,"pll.sca_tdf_sig_ictrl");
	sca_trace(tr, pll.sca_tdf_sig_fout ,"pll.sca_tdf_sig_fout");

	// Start the simulation
	sc_start((double)options["system"]["tsim"], sc_core::SC_SEC);

	// Close trace file and exit
	if(format.compare("vcd") == 0)
		sca_close_vcd_trace_file(tr);
	else
		sca_close_tabular_trace_file(tr);

	cout << "Simulation finished!" << endl;

	return 0;
}
