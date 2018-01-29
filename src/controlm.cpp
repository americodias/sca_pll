#include "controlm.h"

void controlm::init(void) {
	iout.write(0);
}

void controlm::processing(void) { // our workhorse method

	if(vc >= vcc+10e-3 or vc <= 0-10e-3) {
		iout=0;
	} 
	else {
		iout=iin;
	}
}

void controlm::set_attributes(void) {
	iout.set_timestep(tstep,sc_core::SC_SEC);
	iout.set_delay(1);
}

