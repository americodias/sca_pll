#pragma once

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
	sca_tdf::sc_in<bool> up;
	sca_tdf::sc_in<bool> dn;
	sca_tdf::sca_in<double> vc;
	sca_tdf::sca_out<double> iout;

	
	chargepump(sc_module_name name_,
				double tstep_,
				double vcc_,
				double current_up_,
				double current_dn_,
				double current_leak_,
				double mosfet_vth_) ;

	void processing(void);
	void set_attributes(void);
};

