/** @file sca_tdf_chargepump.h
 *  @brief Charge Pump module include file
 *
 *  @author Americo Dias
 *  @date 06/02/2018
 */
#pragma once

/** @cond */
#include "systemc-ams.h"
/** @endcond */

/**
 * Charge Pump module
 */
SCA_TDF_MODULE(sca_tdf_chargepump) {
private:
	// Private variables
	double tstep;
	double vcc;
	double current_up;
	double current_dn;
	double current_leak;
	double mosfet_vth;
	double mosfet_vp;
	double mosfet_vn;

public:
	// Ports
	sca_tdf::sc_in<bool> sc_in_up;				//< Up input
	sca_tdf::sc_in<bool> sc_in_dn;				//< Down input
	sca_tdf::sca_in<double> sca_tdf_in_vctrl;	//< Input of the control voltage (to limit the current)
	sca_tdf::sca_out<double> sca_tdf_out_ictrl; //< Output control current

	/**
	 * @param name_	Module name
	 * @param tstep_ Simulation time-step
	 * @param vcc_ Supply voltage in volts
	 * @param current_up_ Current for charge in amperes
	 * @param current_dn_ Current for discharge in amperes
	 * @param current_leak_ Leak current in amperes
	 * @param mosfet_vth_ Transistors VT in volts
	 */
	sca_tdf_chargepump(sc_module_name name_,
				double tstep_,
				double vcc_,
				double current_up_,
				double current_dn_,
				double current_leak_,
				double mosfet_vth_) ;

	/**
	 * Set module attributes
	 */
	void set_attributes(void);

	/**
	 * Processing thread
	 */
	void processing(void);


};
