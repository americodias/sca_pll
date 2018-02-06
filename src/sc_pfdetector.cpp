/** @file sc_pfdetector.cpp
 *  @brief Phase Frequency Detector implementation
 *
 *  @author Americo Dias
 *  @date 06/02/2018
 */
#include "sc_pfdetector.h"

/**
 * Constructor implementation
 */
sc_pfdetector::sc_pfdetector(sc_module_name name_,
			double tr_,
			double tf_):
			sc_module(name_),
			up_delay("up_delay", tr_, tf_),
			dn_delay("dn_delay", tr_, tf_)
{
	up_delay.in(up_buf);
	up_delay.out(sc_out_up);

	dn_delay.in(dn_buf);
	dn_delay.out(sc_out_dn);

	SC_METHOD(sig_proc)
		sensitive << sc_in_fref.pos() << sc_in_fdiv.pos();
}

/**
 * Processing thread
 */
void sc_pfdetector::sig_proc(void) {
	double diff = sc_in_fref - sc_in_fdiv;

	if(diff > 0) {
		up_buf.write(true);
		dn_buf.write(false);
	} else if (diff < 0) {
		up_buf.write(false);
		dn_buf.write(true);
	} else {
		up_buf.write(false);
		dn_buf.write(false);
	}
}
