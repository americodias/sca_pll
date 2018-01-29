#ifndef __PFDETECTOR_H
#define __PFDETECTOR_H

#include "systemc.h"

SC_MODULE(pfdetector) {
	sc_in<bool> ref;
	sc_in<bool> fdbk;
	sc_out<bool> UP, DN;
	
	SC_CTOR(pfdetector) {
		SC_METHOD(sig_proc)
			sensitive << ref.pos() << fdbk.pos();
	}
	
	void sig_proc(void);
	void set_attributes(void);
};

#endif
