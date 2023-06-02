/**
 * MIT License
 * 
 * Copyright (c) 2018 Américo Dias <americo.dias@gmail.com>
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 * 
 */

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
