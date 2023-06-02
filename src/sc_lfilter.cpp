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

/** @file sc_lfilter.cpp
 *  @brief Loop filter module implementation
 *
 *  @author Americo Dias
 *  @date 06/02/2018
 */
#include "sc_lfilter.h"

/**
 * Constructor implementation
 */
sc_lfilter::sc_lfilter (sc_module_name name_,
		int order_,
		double c1_value_,
		double r2_value_,
		double c2_value_,
		double r3_value_,
		double c3_value_ ):
		sc_module(name_)
{
	// Variables initialization
	order=order_;
	r0_value=1e-6;
	c1_value=c1_value_;
	r2_value=r2_value_;
	c2_value=c2_value_;
	r3_value=r3_value_;
	c3_value=c3_value_;

	// Convert the TDF input to an ELN current
	i_in = new sca_eln::sca_tdf_isource("i_in", 1.0);
	i_in->inp(sca_tdf_in_ictrl);
	i_in->p(gnd);
	i_in->n(node0);

	// Shunt resistor used for debug purposes
	r0 = new sca_eln::sca_r("r0", 1e-6);
	r0->p(node0);
	r0->n(node1);

	// Convert the output voltage from ELN to TDF
	v_cp = new sca_eln::sca_tdf_vsink("v_cp", 1.0);
	v_cp->p(node1);
	v_cp->n(gnd);
	v_cp->outp(sca_tdf_out_vcp);

	c1 = new sca_eln::sca_c("c1", c1_value);
	c1->p(node1);
	c1->n(gnd);

	// First part
	r2 = new sca_eln::sca_r("r2", r2_value);
	r2->p(node1);
	r2->n(node2);
	c2 = new sca_eln::sca_c("c2", c2_value);
	c2->p(node2);
	c2->n(gnd);

	// Convert the output voltage from ELN to TDF
	v_out = new sca_eln::sca_tdf_vsink("v_vout", 1.0);
	v_out->n(gnd);
	v_out->outp(sca_tdf_out_vctrl);

	if(order==2) {
		v_out->p(node1);
	}
	if(order==3) {
		// If the order is 3, add the extra components
		r3 = new sca_eln::sca_r("r3", r3_value);
		c3 = new sca_eln::sca_c("c3", c3_value);
		r3->p(node1);
		r3->n(node3);
		c3->p(node3);
		c3->n(gnd);
		v_out->p(node3);
	}

}
