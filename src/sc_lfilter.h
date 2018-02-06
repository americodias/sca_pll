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
	double r1_value;
	double c1_value;
	double c2_value;
	double r3_value;
	double c3_value;

	// Circuit nodes
	sca_eln::sca_node node0, node1, node2, node3;
	sca_eln::sca_node_ref gnd;

	// Circuit components
	sca_eln::sca_r *r0;
	sca_eln::sca_r *r1;
	sca_eln::sca_c *c1;
	sca_eln::sca_c *c2;
	sca_eln::sca_r *r3;
	sca_eln::sca_c *c3;

	// Conversion TDF->ELN->TDF
	sca_eln::sca_tdf_isource *i_in;
	sca_eln::sca_tdf_vsink *v_out;

public:
	// Ports
	sca_tdf::sca_in<double> sca_tdf_in_ictrl;	//< Input control current
	sca_tdf::sca_out<double> sca_tdf_out_vctrl;	//< Output control voltage

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
				double r1_value_,
				double c1_value_,
				double c2_value_,
				double r3_value_,
				double c3_value_ );

};
