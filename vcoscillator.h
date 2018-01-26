#ifndef __VCOSCILLATOR_H
#define __VCOSCILLATOR_H

#include "systemc-ams.h"
#include "config.h"

SCA_TDF_MODULE(vcoscillator) {
public:
	sca_tdf::sca_out<double> out; // output port
	sca_tdf::sca_out<double> freq; // output port
	sca_tdf::sca_in<double> vc; 
	
	SCA_CTOR(vcoscillator) {} // constructor does nothing here 
	
	void processing(void);
	void set_attributes(void);
};

#endif