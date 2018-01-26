#ifndef __DIVIDER_H
#define __DIVIDER_H

#include "systemc-ams.h"
#include "config.h"

SCA_TDF_MODULE(divider) {
private:
	bool state=false;
	bool state_div=false;
	unsigned long counter=0;
	
public:
	sca_tdf::sca_in<double> in;
	sca_tdf::sc_out<bool> out;
	unsigned long factor;
	
	SCA_CTOR(divider) {} // constructor does nothing here 
	
	void init(void);
	void processing(void);

};

#endif