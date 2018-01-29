/*
 * delay.h
 *
 *  Created on: 28. jan. 2018
 *      Author: ADias
 */

#pragma once

#include "systemc-ams.h"

SC_MODULE (delay){
private:
	double tr;
	double tf;

public:
	sc_in<bool> in;
	sc_out<bool> out;

	void init(void);

	SC_HAS_PROCESS(delay);
	void delay_thread();

	delay(sc_module_name name_,
				double tr_,
				double tf_):
				sc_module(name_),
				tr(tr_),
				tf(tf_) {

		SC_THREAD(delay_thread);
	}
};


