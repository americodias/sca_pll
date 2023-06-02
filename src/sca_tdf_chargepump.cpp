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

/** @file sca_tdf_chargepump.cpp
 *  @brief Charge Pump module implementation
 *
 *  @author Americo Dias
 *  @date 06/02/2018
 */
#include "sca_tdf_chargepump.h"

/**
 * Constructor implementation
 */
sca_tdf_chargepump::sca_tdf_chargepump(sc_module_name name_,
		double tstep_,
		double vdd_,
		double current_up_,
		double current_dn_,
		double current_leak_,
		double mosfet_vth_):
		sca_module(name_) {

	tstep=tstep_;
	vdd=vdd_;
	current_up=current_up_;
	current_dn=current_dn_;
	current_leak=current_leak_;
	mosfet_vth=mosfet_vth_;
	mosfet_vtp=mosfet_vth_;
	mosfet_vtn=vdd-mosfet_vth_;

}

/**
 * Set module attributes
 */
void sca_tdf_chargepump::set_attributes(void) {
	sca_tdf_out_ictrl.set_timestep(tstep,sc_core::SC_SEC);
	sca_tdf_out_ictrl.set_delay(1);
}

/**
 * Processing thread
 */
void sca_tdf_chargepump::processing(void) {

	double charge = 0,
			discharge = 0,
			mismatch = 0,
			i = 0;

	// Discharge (NMOS)
	if(sca_tdf_in_vcp>mosfet_vtn) {
		// Saturation
		discharge=-current_dn;
	} else {
		// Triode
		double vds = sca_tdf_in_vcp;
		discharge=-((2.0/(vdd-mosfet_vth))*current_dn*vds-(1.0/pow(vdd-mosfet_vth,2.0))*current_dn*pow(vds,2.0));
	}

	// Charge (PMOS)
	if(sca_tdf_in_vcp<mosfet_vtp) {
		// Saturation
		charge=current_up;
	} else {
		// Triode
		double vds = vdd-sca_tdf_in_vcp;
		charge=(2.0/(vdd-mosfet_vth))*current_up*vds-(1.0/pow(vdd-mosfet_vth,2.0))*current_up*pow(vds,2.0);
	}

	mismatch=charge+discharge;


	/**
	 * Set the output current depending on the inputs state
	 * (up/down)
	 */
	if(sc_in_up && !sc_in_dn) {
		i = charge;
	}
	else if(!sc_in_up && sc_in_dn) {
		i = discharge;
	}
	else if(!sc_in_up && !sc_in_dn) {
		i = -current_leak;
	}
	else if(sc_in_up && sc_in_dn) {
		i = mismatch;
	}

	/**
	 * Limit the output current if the loop filter input voltage
	 * is out of limits (V_CTRL < 0 || V_CTRL > vdd)
	 */
	if((sca_tdf_in_vcp>vdd && i>0) || (sca_tdf_in_vcp<0 && i<0)) {
		i=0;
	}

	sca_tdf_out_ictrl = i;
}
