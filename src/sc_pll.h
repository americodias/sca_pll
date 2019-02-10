/** @file sc_pll.h
 *  @brief Phase Locked Loop top level module include file
 *
 *  @author Americo Dias
 *  @date 06/02/2018
 */
#pragma once

/** @cond */
#include "systemc.h"
#include "systemc-ams.h"
/** @endcond */
#include "sc_lfilter.h"
#include "sca_tdf_divider.h"
#include "sc_pfdetector.h"
#include "sca_tdf_chargepump.h"
#include "sca_tdf_vcoscillator.h"

/**
 * Phase Locked Loop top level module
 */
SC_MODULE(sc_pll) {
public:
	// Building blocks
	sc_pfdetector 				*sc_pf;
	sc_lfilter 					*sc_lf;
	sca_tdf_divider 			*sca_tdf_div;
	sca_tdf_chargepump 			*sca_tdf_cp;
	sca_tdf_vcoscillator 		*sca_tdf_vco;

	// Signals
	sc_signal<bool>				sc_sig_up;
	sc_signal<bool> 			sc_sig_dn;
	sc_signal<bool> 			sc_sig_fdiv;
	sca_tdf::sca_signal<double> sca_tdf_sig_vcp;
	sca_tdf::sca_signal<double> sca_tdf_sig_vctrl;
	sca_tdf::sca_signal<double> sca_tdf_sig_ictrl;
	sca_tdf::sca_signal<double> sca_tdf_sig_fout;

	// Ports
	sc_in<bool> 				*sc_in_fref;
	//sca_tdf::sca_out<double> 	*sca_tdf_out_fout;
	sca_tdf::sca_out<double> 	*sca_tdf_out_fout_freq;

	/**
	 * NOTE: All units in SI
	 *
	 * @param name_ Module name
	 * @param tr_ Rise time
	 * @param tf_ Fall time
	 * @param tstep_ Simulation time-step
	 * @param vdd_ Supply voltage
	 * @param current_up_ Charge current
	 * @param current_dn_ Discharge current
	 * @param current_leak_ Leakage current in the charge pump
	 * @param mosfet_vth_ Transistors VT
	 * @param order_ Order of the loop filter (2 or 3)
	 * @param r1_value_	R1 value
	 * @param c1_value_ C1 value
	 * @param c2_value_ C2 value
	 * @param r3_value_ R3 value
	 * @param c3_value_ C3 value
	 * @param vcm_ Common mode voltage
	 * @param kvo_ VCO gain
	 * @param fmin_ VCO minimum frequency when the control voltage is zero
	 * @param factor_ Divider factor
	 */
	sc_pll(sc_module_name name_,
			// Charge pump
			double tstep_,
			double vdd_,
			double current_up_,
			double current_dn_,
			double current_leak_,
			double mosfet_vth_,
			// Loop filter
			int order_,
			double c1_value_,
			double r2_value_,
			double c2_value_,
			double r3_value_,
			double c3_value_,
			// Voltage controlled oscillator
			//double tstep_,
			//double vdd_,
			double vcm_,
			double kvo_,
			double fmin_,
			// Divider
			//double vcm_,
			unsigned int factor_ );
};
