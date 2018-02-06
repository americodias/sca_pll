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
		double r1_value_,
		double c1_value_,
		double c2_value_,
		double r3_value_,
		double c3_value_ ):
		sc_module(name_)
{
	// Variables initialization
	order=order_;
	r0_value=1e-6;
	r1_value=r1_value_;
	c1_value=c1_value_;
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

	// First part
	r1 = new sca_eln::sca_r("r1", r1_value);
	r1->p(node1);
	r1->n(node2);
	c1 = new sca_eln::sca_c("c1", c1_value);
	c1->p(node2);
	c1->n(gnd);
	c2 = new sca_eln::sca_c("c2", c2_value);
	c2->p(node1);
	c2->n(gnd);

	// Convert the output voltage from ELN to TDF
	v_out = new sca_eln::sca_tdf_vsink("v_vout1", 1.0);
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
