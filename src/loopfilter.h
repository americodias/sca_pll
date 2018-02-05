/*
 * loopfilter.h
 *
 *  Created on: 28. jan. 2018
 *      Author: ADias
 */

#pragma once

#include "systemc-ams.h"

SC_MODULE(loopfilter) {
private:
	int order;
	double r0_value;
	double r1_value;
	double c1_value;
	double c2_value;
	double r3_value;
	double c3_value;

public:
	sca_tdf::sca_in<double> in;
	sca_tdf::sca_out<double> out;

	sca_eln::sca_node node0, node1, node2, node3;
	sca_eln::sca_node_ref gnd;

	sca_eln::sca_r *r0;
	sca_eln::sca_r *r1;
	sca_eln::sca_c *c1;
	sca_eln::sca_c *c2;
	sca_eln::sca_r *r3;
	sca_eln::sca_c *c3;

	sca_eln::sca_tdf_isource *i_in;
	sca_eln::sca_tdf_vsink *v_out;

	loopfilter (sc_module_name name_,
				int order_,
				double r1_value_,
				double c1_value_,
				double c2_value_,
				double r3_value_,
				double c3_value_ );

};


