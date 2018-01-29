#ifndef __VCOSCILLATOR_H
#define __VCOSCILLATOR_H

#include "systemc-ams.h"

SCA_TDF_MODULE(vcoscillator) {
private:
	double tstep;
	double vcc;
	double vcm;
	double kvo;
	double fmin;
public:
	sca_tdf::sca_out<double> out; // output port
	sca_tdf::sca_out<double> freq; // output port
	sca_tdf::sca_in<double> vc; 
	
	/*
	SCA_CTOR(vcoscillator) {} // constructor does nothing here 
	*/

	vcoscillator(sc_module_name name_,
				double tstep_,
				double vcc_,
				double vcm_,
				double kvo_,
				double fmin_):
				sca_module(name_),
				tstep(tstep_),
				vcc(vcc_),
				vcm(vcm_),
				kvo(kvo_),
				fmin(fmin_) {}
	
	void processing(void);
	void set_attributes(void);
};

#endif
