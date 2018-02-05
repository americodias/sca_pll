#include <iostream>
#include <fstream>
#include "include/json.hpp"
#include "include/cxxopts.hpp"

#include "systemc.h"
#include "systemc-ams.h"
#include "chargepump.h"
#include "loopfilter.h"
#include "vcoscillator.h"
#include "divider.h"
#include "pfdetector.h"
#include "delay.h"

using namespace std;
using json = nlohmann::json;

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

int sc_main(int argc, char* argv[]){

	json options;
	string format;

	cout << endl << endl;

	try
	{
		cxxopts::Options opt(argv[0], "PLL simulator");
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

		string config_filename = result["config"].as<std::string>();
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

		options = get_options(config_filename);

	} catch (const cxxopts::OptionException& e)
	{
		std::cout << "error parsing options: " << e.what() << std::endl;
		exit(-1);
	}

	sc_clock sig_fref ("sig_fref", sc_time(1/(double)options["system"]["fref"], sc_core::SC_SEC), 0.5, sc_time(0.5/(double)options["system"]["fref"], sc_core::SC_SEC));


	sc_signal<bool> sig_fdiv;
	sc_signal<bool> sig_UP;
	sc_signal<bool> sig_DN;
	sca_tdf::sca_signal<double> sig_fout;
	sca_tdf::sca_signal<double> sig_vc;
	sca_tdf::sca_signal<double> sig_icp;
	sca_tdf::sca_signal<double> sig_icp_limited;
	sca_tdf::sca_signal<double> sig_freq;


	pfdetector   pfd("pfd",
			(double)options["phase_detector"]["tr"],
			(double)options["phase_detector"]["tf"]);

	chargepump   cpump("cpump",
			(double)options["system"]["tstep"],
			(double)options["system"]["vcc"],
			(double)options["charge_pump"]["current_up"],
			(double)options["charge_pump"]["current_dn"],
			(double)options["charge_pump"]["current_leak"],
			(double)options["charge_pump"]["mosfet_vth"]);

	loopfilter   lfilter("lfilter",
			(int)options["loop_filter"]["order"],
			(double)options["loop_filter"]["r1"],
			(double)options["loop_filter"]["c1"],
			(double)options["loop_filter"]["c2"],
			(double)options["loop_filter"]["r3"],
			(double)options["loop_filter"]["c3"]);

	vcoscillator vco("vco",
			(double)options["system"]["tstep"],
			(double)options["system"]["vcc"],
			(double)options["system"]["vcm"],
			(double)options["vco"]["kvo"],
			(double)options["vco"]["fmin"] );

	divider      dv("div",
			(double)options["system"]["vcm"],
			(double)options["divider"]["n"]);


	pfd.ref(sig_fref);
	pfd.fdbk(sig_fdiv);
	pfd.up(sig_UP);
	pfd.dn(sig_DN);

	cpump.up(sig_UP);
	cpump.dn(sig_DN);
	cpump.iout(sig_icp);
	cpump.vc(sig_vc);

	lfilter.in(sig_icp);
	lfilter.out(sig_vc);

	vco.out(sig_fout);
	vco.vc(sig_vc);
	vco.freq(sig_freq);

	dv.in(sig_fout);
	dv.out(sig_fdiv);

	//sig_vc.set(2.5);
	cout << "Info: Simulation options:" << endl;
	cout << "         Simulation time:     " << (double)options["system"]["tsim"] << endl;
	cout << "         Simulation timestep: " << (double)options["system"]["tstep"] << endl;
	cout << "         Ouput format:        " << format << endl;

	sca_trace_file* tr;

	if(format.compare("vcd") == 0)
		tr = sca_create_vcd_trace_file("output"); // Usual SystemC tracing
	else
		tr = sca_create_tabular_trace_file("output"); // Usual SystemC tracing

	sca_trace(tr, sig_fout ,"sig_fout");
	sca_trace(tr, sig_freq ,"sig_freq");
	sca_trace(tr, sig_fref ,"sig_fref");
	sca_trace(tr, sig_fdiv ,"sig_fdiv");
	sca_trace(tr, sig_UP ,"sig_UP");
	sca_trace(tr, sig_DN ,"sig_DN");
	sca_trace(tr, sig_vc ,"sig_vc");
	sca_trace(tr, sig_icp ,"sig_icp");


	sc_start((double)options["system"]["tsim"], sc_core::SC_SEC);

	if(format.compare("vcd") == 0)
		sca_close_vcd_trace_file(tr);
	else
		sca_close_tabular_trace_file(tr);

	cout << "Simulation finished!" << endl;

	return 0;
}
