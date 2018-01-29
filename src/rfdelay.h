/*
 * rfdelay.h
 *
 *  Created on: 28. jan. 2018
 *      Author: ADias
 */

#ifndef RFDELAY_H_
#define RFDELAY_H_

#include "systemc-ams.h"

SC_MODULE (rfdelay){
private:
	double vcc;

public:
	sc_in<bool> in;
	sc_out<double> out;

	void prc_rfdelay();

	rfdelay(sc_module_name name_,
				double vcc_):
				sc_module(name_),
				vcc(vcc_) {

		SC_THREAD(prc_rfdelay);
	}

	SC_HAS_PROCESS(rfdelay);



};

#endif /* RFDELAY_H_ */
