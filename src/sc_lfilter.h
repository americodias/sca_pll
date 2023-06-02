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

/** @file sc_lfilter.h
 *  @brief Loop filter module include file
 *
 *  @author Americo Dias
 *  @date 06/02/2018
 */
#pragma once

/** @cond */
#include "systemc-ams.h"
/** @endcond */

/**
 * Loop filter module
 */
SC_MODULE(sc_lfilter) {
private:
	// Private variables
	int order;
	double r0_value;
	double c1_value;
	double r2_value;
	double c2_value;
	double r3_value;
	double c3_value;

	// Circuit nodes
	sca_eln::sca_node node0, node1, node2, node3;
	sca_eln::sca_node_ref gnd;

	// Circuit components
	sca_eln::sca_r *r0;
	sca_eln::sca_c *c1;
	sca_eln::sca_r *r2;
	sca_eln::sca_c *c2;
	sca_eln::sca_r *r3;
	sca_eln::sca_c *c3;

	// Conversion TDF->ELN->TDF
	sca_eln::sca_tdf_isource *i_in;
	sca_eln::sca_tdf_vsink *v_cp;
	sca_eln::sca_tdf_vsink *v_out;

public:
	// Ports
	sca_tdf::sca_in<double> sca_tdf_in_ictrl;	//< Input control current
	sca_tdf::sca_out<double> sca_tdf_out_vcp;	//< Voltage of the input node (charge pump)
	sca_tdf::sca_out<double> sca_tdf_out_vctrl;	//< Voltage of the output (=v_cp for the 2nd order filter)

	/**
	 * @param name_ Name of the module
	 * @param order_ Filter order (2 or 3)
	 * @param r1_value_	R1 value in ohms
	 * @param c1_value_ C1 value in farads
	 * @param c2_value_ C2 value in farads
	 * @param r3_value_ R3 value in ohms
	 * @param c3_value_ C3 value in farads
	 */
	sc_lfilter (sc_module_name name_,
				int order_,
				double c1_value_,
				double r2_value_,
				double c2_value_,
				double r3_value_,
				double c3_value_ );

};
