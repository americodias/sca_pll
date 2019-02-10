/** @file sc_pfdetector.h
 *  @brief Phase Frequency Detector module include file
 *
 *  @author Americo Dias
 *  @date 06/02/2018
 */
#pragma once

/** @cond */
#include "systemc.h"
/** @endcond */

//#include "sc_delay.h"

#define IDLE 0
#define UP 1
#define DN -1

/**
 * Phase Frequency Detector module
 */
SC_MODULE(sc_pfdetector) {
private:
	// Private variables

public:
	// Ports
	sc_in<bool> sc_in_fref; 	//< Reference clock
	sc_in<bool> sc_in_fdiv;		//< Divided output frequency
	sc_out<bool> sc_out_up;		//< Up output
	sc_out<bool> sc_out_dn;		//< Down output

	SC_HAS_PROCESS(sc_pfdetector);

	/**
	 * @param name_ Name of the module
	 * @param tr_ Rise time
	 * @param tf_ Fall time
	 */
	sc_pfdetector(sc_module_name name_);

	/**
	 * Processing thread
	 */
	void sig_proc(void);
};
