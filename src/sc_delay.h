/** @file sc_delay.h
 *  @brief Delay module include file
 *
 *  @author Americo Dias
 *  @date 06/02/2018
 */
#pragma once
/** @cond */
#include "systemc-ams.h"
/** @endcond */

/**
 * Delay module
 */
SC_MODULE (sc_delay){
private:
	double tr;		// Rise time
	double tf;		// Fall time

public:
	sc_in<bool> in;
	sc_out<bool> out;

	SC_HAS_PROCESS(sc_delay);

	/**
	 * Processing thread
	 */
	void delay_thread(void);

	/**
	 * @param name_ Name of the module
	 * @param tr_ Rise time
	 * @param tf_ Fall time
	 */
	sc_delay(sc_module_name name_,
				double tr_,
				double tf_):
				sc_module(name_),
				tr(tr_),
				tf(tf_) {

		SC_THREAD(delay_thread);
	}
};
