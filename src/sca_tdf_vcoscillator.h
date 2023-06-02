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
