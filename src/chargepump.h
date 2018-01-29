#ifndef __CHARGEPUMP_H
#define __CHARGEPUMP_H

#include "systemc-ams.h"

SCA_TDF_MODULE(chargepump) {
private:
	double tstep;
	double vcc;
	double current_up;
	double current_dn;
	double current_leak;
	double mosfet_vth;
	double mosfet_vp;
	double mosfet_vn;

public:
	sca_tdf::sc_in<double> UP;
	sca_tdf::sc_in<double> DN;
	sca_tdf::sca_out<double> out;
	sca_tdf::sca_in<double> vc;
	
	chargepump(sc_module_name name_,
				double tstep_,
				double vcc_,
				double current_up_,
				double current_dn_,
				double current_leak_,
				double mosfet_vth_) :
				sca_module(name_),
				tstep(tstep_),
				vcc(vcc_),
				current_up(current_up_),
				current_dn(current_dn_),
				current_leak(current_leak_),
				mosfet_vth(mosfet_vth_),
				mosfet_vp(vcc_-mosfet_vth_),
				mosfet_vn(mosfet_vth_) {}

	void processing(void);
	void set_attributes(void);
};

#endif
