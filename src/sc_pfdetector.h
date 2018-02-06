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

#include "sc_delay.h"

/**
 * Phase Frequency Detector module
 */
SC_MODULE(sc_pfdetector) {
private:
	// Private variables
	sc_delay up_delay;
	sc_delay dn_delay;
	sc_signal<bool> up_buf;
	sc_signal<bool> dn_buf;

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
	sc_pfdetector(sc_module_name name_,
				double tr_,
				double tf_);

	/**
	 * Processing thread
	 */
	void sig_proc(void);
};
