#ifndef __CHARGEPUMP_H
#define __CHARGEPUMP_H

#include "systemc-ams.h"
#include "config.h"

SCA_TDF_MODULE(chargepump) {
	sca_tdf::sc_in<bool> UP;
	sca_tdf::sc_in<bool> DN;
	sca_tdf::sca_out<double> out;
	
	double currentup=10e-6;
	double currentdw=currentup;
	double leakage=100e-9;
	double vt=0.7;
	double min=vt;
	double max=VCC-vt;
	double iout=0;
	double vc=3.3;
	
	double fp=1e6;
	double cap=20e-12;
	double tau=0;
	double tn1=0;
	
	SCA_CTOR(chargepump) {} // constructor does nothing here 
	
	void init(void);
	void processing(void);
	//void sig_proc(void);
	void set_attributes(void);
	
};

#endif
