#include "systemc.h"
#include "systemc-ams.h"
#include "config.h"
#include "chargepump.h"
#include "vcoscillator.h"
#include "divider.h"
#include "pfdetector.h"


int sc_main(int argc, char* argv[]){
	//sc_report_handler::set_actions (SC_INFO, SC_DO_NOTHING);
	
	sc_clock sig_fref ("sig_fref", sc_time(1/FREF, sc_core::SC_SEC), 0.5, sc_time(0.5/FREF, sc_core::SC_SEC));
	sc_signal<bool> sig_fdiv;
	sc_signal<bool> sig_UP;
	sc_signal<bool> sig_DN;
	sca_tdf::sca_signal<double> sig_fout;
	sca_tdf::sca_signal<double> sig_vc;
	sca_tdf::sca_signal<double> sig_freq;
			
	pfdetector   pfd("pfd");
	vcoscillator vco("vco");
	divider      dv("div");
	chargepump   cpump("cpump");
	
	pfd.ref(sig_fref);
	pfd.fdbk(sig_fdiv);
	pfd.UP(sig_UP);
	pfd.DN(sig_DN);
	
	vco.out(sig_fout);
	vco.vc(sig_vc);
	vco.freq(sig_freq);
	
	dv.in(sig_fout);
	dv.out(sig_fdiv);
	dv.factor = 2450;
	
	cpump.UP(sig_UP);
	cpump.DN(sig_DN);
	cpump.out(sig_vc);
	
	//sig_vc.set(2.5);
	cout << "Starting simulation" << endl;
	cout << "Simulation time: " << TSIM << endl;
	cout << "Simulation timestep: " << TSTEP << endl;
	cout << "Start generating signal.vcd file" << endl;
	
	sca_trace_file* tr = sca_create_vcd_trace_file("signal"); // Usual SystemC tracing
	//sca_trace(tr, sig_fout ,"sig_fout");

	sca_trace(tr, sig_fref ,"sig_fref");
	sca_trace(tr, sig_fdiv ,"sig_fdiv");
	sca_trace(tr, sig_UP ,"sig_UP");
	sca_trace(tr, sig_DN ,"sig_DN");
	sca_trace(tr, sig_vc ,"sig_vc");
	sca_trace(tr, sig_freq ,"sig_freq");
	
	sc_start(TSIM, sc_core::SC_SEC);
	
    sca_close_vcd_trace_file(tr);
    cout << "Finished generating signal.vcd file" << endl;

	return 0;
}
