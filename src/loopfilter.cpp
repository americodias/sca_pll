/*
 * loopfilter.cpp
 *
 *  Created on: 28. jan. 2018
 *      Author: ADias
 */

#include "loopfilter.h"


loopfilter::loopfilter (sc_module_name name_,
		int order_,
		double r1_value_,
		double c1_value_,
		double c2_value_,
		double r3_value_,
		double c3_value_ ):
		sc_module(name_)
{
	order=order_;
	r0_value=1e-6;
	r1_value=r1_value_;
	c1_value=c1_value_;
	c2_value=c2_value_;
	r3_value=r3_value_;
	c3_value=c3_value_;


	i_in = new sca_eln::sca_tdf_isource("i_in", 1.0);
	i_in->inp(in);
	i_in->p(gnd);
	i_in->n(node0);

	r0 = new sca_eln::sca_r("r0", 1e-6);
	r0->p(node0);
	r0->n(node1);

	r1 = new sca_eln::sca_r("r1", r1_value);
	r1->p(node1);
	r1->n(node2);
	c1 = new sca_eln::sca_c("c1", c1_value);
	c1->p(node2);
	c1->n(gnd);
	c2 = new sca_eln::sca_c("c2", c2_value);
	c2->p(node1);
	c2->n(gnd);

	v_out = new sca_eln::sca_tdf_vsink("v_vout1", 1.0);
	v_out->p(node1);
	v_out->n(gnd);

	if(order==3) {
		r3 = new sca_eln::sca_r("r3", r3_value);
		c3 = new sca_eln::sca_c("c3", c3_value);
		r3->p(node1);
		r3->n(node3);
		c3->p(node3);
		c3->n(gnd);
		v_out->p(node3);
	}

	v_out->outp(out);

}

