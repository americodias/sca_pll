#include <iostream>
#include <fstream>
#include "include/json.hpp"

#include "systemc.h"
#include "systemc-ams.h"
#include "chargepump.h"
#include "loopfilter.h"
#include "vcoscillator.h"
#include "divider.h"
#include "pfdetector.h"
#include "controlm.h"
#include "rfdelay.h"

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
	//sc_report_handler::set_actions (SC_INFO, SC_DO_NOTHING);
	
	if(argc < 2) {
		cout << "Error: Not enough arguments" << endl;
		cout << "Usage: " << argv[0] << " options_file" << endl;
		return -1;
	}

	json options = get_options(argv[1]);

	sc_clock sig_fref ("sig_fref", sc_time(1/(double)options["system"]["fref"], sc_core::SC_SEC), 0.5, sc_time(0.5/(double)options["system"]["fref"], sc_core::SC_SEC));


	sc_signal<bool> sig_fdiv;
	sc_signal<bool> sig_UP;
	sc_signal<bool> sig_DN;
	sc_signal<double> sig_UP_d;
	sc_signal<double> sig_DN_d;
	sca_tdf::sca_signal<double> sig_fout;
	sca_tdf::sca_signal<double> sig_vc;
	sca_tdf::sca_signal<double> sig_icp;
	sca_tdf::sca_signal<double> sig_icp_limited;
	sca_tdf::sca_signal<double> sig_freq;


	pfdetector   pfd("pfd");
	vcoscillator vco("vco",
						(double)options["system"]["tstep"],
						(double)options["system"]["vcc"],
						(double)options["system"]["vcm"],
						(double)options["vco"]["kvo"],
						(double)options["vco"]["fmin"] );
	divider      dv("div", (double)options["system"]["vcm"], 2450);
	chargepump   cpump("cpump",
						(double)options["system"]["tstep"],
						(double)options["system"]["vcc"],
						(double)options["charge_pump"]["current_up"],
						(double)options["charge_pump"]["current_dn"],
						(double)options["charge_pump"]["current_leak"],
						(double)options["charge_pump"]["mosfet_vth"]);
	loopfilter   lfilter("lfilter",
						(double)options["loop_filter"]["r1"],
						(double)options["loop_filter"]["c1"],
						(double)options["loop_filter"]["c2"],
						(double)options["loop_filter"]["r3"],
						(double)options["loop_filter"]["c3"]);
	controlm     cm("cm",
						(double)options["system"]["tstep"],
						(double)options["system"]["vcc"]);

	rfdelay		 rfd1("rfd1", (double)options["system"]["vcc"]);
	rfdelay		 rfd2("rfd2", (double)options["system"]["vcc"]);

	pfd.ref(sig_fref);
	pfd.fdbk(sig_fdiv);
	pfd.UP(sig_UP);
	pfd.DN(sig_DN);

	rfd1.in(sig_UP);
	rfd1.out(sig_UP_d);

	rfd2.in(sig_DN);
	rfd2.out(sig_DN_d);

	vco.out(sig_fout);
	vco.vc(sig_vc);
	vco.freq(sig_freq);
	
	dv.in(sig_fout);
	dv.out(sig_fdiv);
	
	cpump.UP(sig_UP_d);
	cpump.DN(sig_DN_d);
	cpump.out(sig_icp);
	cpump.vc(sig_vc);

	lfilter.in(sig_icp_limited);
	lfilter.out(sig_vc);

	cm.iin(sig_icp);
	cm.vc(sig_vc);
	cm.iout(sig_icp_limited);
	
	//sig_vc.set(2.5);
	cout << "Starting simulation" << endl;
	cout << "Simulation time: " << (double)options["system"]["tsim"] << endl;
	cout << "Simulation timestep: " << (double)options["system"]["tstep"] << endl;
	cout << "Start generating signal.vcd file" << endl;
	
	sca_trace_file* tr = sca_create_vcd_trace_file("signal"); // Usual SystemC tracing
	//sca_trace_file* tr_csv = sca_create_tabular_trace_file("signal");
	//sca_trace(tr, sig_fout ,"sig_fout");

	sca_trace(tr, sig_fref ,"sig_fref");
	sca_trace(tr, sig_fdiv ,"sig_fdiv");
	sca_trace(tr, sig_UP ,"sig_UP");
	sca_trace(tr, sig_DN ,"sig_DN");
	sca_trace(tr, sig_UP_d ,"sig_UP_d");
	sca_trace(tr, sig_DN_d ,"sig_DN_d");
	sca_trace(tr, sig_vc ,"sig_vc");
	sca_trace(tr, sig_freq ,"sig_freq");
	sca_trace(tr, sig_icp ,"sig_icp");
	sca_trace(tr, sig_icp_limited ,"sig_icp_limited");

	//sca_trace(tr_csv, sig_freq ,"sig_freq");
	//sca_trace(tr_csv, sig_UP ,"sig_UP");
	//sca_trace(tr_csv, sig_DN ,"sig_DN");
	
	sc_start((double)options["system"]["tsim"], sc_core::SC_SEC);
	
    sca_close_vcd_trace_file(tr);
	//sca_close_tabular_trace_file(tr_csv);
    cout << "Finished generating signal.vcd file" << endl;

	return 0;
}
