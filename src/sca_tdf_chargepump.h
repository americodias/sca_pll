/**
 * MIT License
 * 
 * Copyright (c) 2018 Américo Dias <americo.dias@gmail.com>
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 * 
 */

/** @file sca_tdf_chargepump.h
 *  @brief Charge Pump module include file
 *
 *  @author Americo Dias
 *  @date 06/02/2018
 */
#pragma once

/** @cond */
#include "systemc-ams.h"
#include <cmath>
/** @endcond */

/**
 * Charge Pump module
 */
SCA_TDF_MODULE(sca_tdf_chargepump) {
private:
	// Private variables
	double tstep;
	double vdd;
	double current_up;
	double current_dn;
	double current_leak;
	double mosfet_vth;
	double mosfet_vtp;
	double mosfet_vtn;

public:
	// Ports
	sca_tdf::sc_in<bool> sc_in_up;				//< Up input
	sca_tdf::sc_in<bool> sc_in_dn;				//< Down input
	sca_tdf::sca_in<double> sca_tdf_in_vcp;		//< Input of the charge pump voltage (to limit the current)
	sca_tdf::sca_out<double> sca_tdf_out_ictrl; //< Output control current

	/**
	 * @param name_	Module name
	 * @param tstep_ Simulation time-step
	 * @param vdd_ Supply voltage in volts
	 * @param current_up_ Current for charge in amperes
	 * @param current_dn_ Current for discharge in amperes
	 * @param current_leak_ Leak current in amperes
	 * @param mosfet_vth_ Transistors VT in volts
	 */
	sca_tdf_chargepump(sc_module_name name_,
				double tstep_,
				double vdd_,
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
