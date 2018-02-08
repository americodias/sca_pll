/** @file sca_tdf_vcoscillator.h
 *  @brief Voltage Controlled Oscillator module include file
 *
 *  @author Americo Dias
 *  @date 06/02/2018
 */
#pragma once
/** @cond */
#include "systemc-ams.h"
/** @endcond */

/**
 * Voltage Controlled Oscillator module
 */
SCA_TDF_MODULE(sca_tdf_vcoscillator) {
private:
	// Private variables
	double tstep;
	double vdd;
	double vcm;
	double kvo;
	double fmin;
public:
	// Ports
	sca_tdf::sca_in<double> sca_tdf_in_vctrl;			//< Voltage control input
	sca_tdf::sca_out<double> sca_tdf_out_fout;			//< Output signal
	sca_tdf::sca_out<double> sca_tdf_out_fout_freq; 	//< Frequency of the output signal

	/**
	 * @param name_ Module name
	 * @param tstep_ Simulation time-step
	 * @param vdd_ Supply voltage in volts
	 * @param vcm_ Common mode voltage in volts (DC level of the output signal)
	 * @param kvo_ VCO gain
	 * @param fmin_ Minimum frequency when the control voltage is zero
	 */
	sca_tdf_vcoscillator(sc_module_name name_,
				double tstep_,
				double vdd_,
				double vcm_,
				double kvo_,
				double fmin_):
				sca_module(name_),
				tstep(tstep_),
				vdd(vdd_),
				vcm(vcm_),
				kvo(kvo_),
				fmin(fmin_) {}

	/**
	 * Set module attributes
	 */
	void set_attributes(void);
	
	/**
	 * Processing thread
	 */
	void processing(void);

};
