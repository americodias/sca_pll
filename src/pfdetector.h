#pragma once

#include "systemc.h"
#include "delay.h"

SC_MODULE(pfdetector) {
private:
	delay up_delay;
	delay dn_delay;
	sc_signal<bool> up_buf;
	sc_signal<bool> dn_buf;

public:

	sc_in<bool> ref;
	sc_in<bool> fdbk;
	sc_out<bool> up;
	sc_out<bool> dn;
	
	SC_HAS_PROCESS(pfdetector);

	pfdetector(sc_module_name name_,
				double tr_,
				double tf_):
				sc_module(name_),
				up_delay("up_delay", tr_, tf_),
				dn_delay("dn_delay", tr_, tf_)
	{
		up_delay.in(up_buf);
		up_delay.out(up);

		dn_delay.in(dn_buf);
		dn_delay.out(dn);
		
		SC_METHOD(sig_proc)
			sensitive << ref.pos() << fdbk.pos();			
	}

	void sig_proc(void);
	void set_attributes(void);
};


