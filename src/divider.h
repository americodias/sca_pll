#ifndef __DIVIDER_H
#define __DIVIDER_H

#include "systemc-ams.h"

SCA_TDF_MODULE(divider) {
private:
	double vcm;
	unsigned int factor;

	bool state=false;
	bool state_div=false;
	unsigned long counter=0;
	
public:
	sca_tdf::sca_in<double> in;
	sca_tdf::sc_out<bool> out;

	divider(sc_module_name name_,
				double vcm_,
				double factor_):
				sca_module(name_),
				vcm(vcm_),
				factor(factor_) {}
	
	void init(void);
	void processing(void);

};

#endif
