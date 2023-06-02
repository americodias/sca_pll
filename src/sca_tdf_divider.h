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

/** @file sca_tdf_divider.h
 *  @brief Frequency divider module include file
 *
 *  @author Americo Dias
 *  @date 06/02/2018
 */
#pragma once

/** @cond */
#include "systemc-ams.h"
/** @endcond */

/**
 * Frequency divider module
 */
SCA_TDF_MODULE(sca_tdf_divider) {
private:
	// Private variables
	double vcm;
	unsigned int factor;

	bool state=false;
	bool state_div=false;
	unsigned long counter=0;
	
public:
	// Ports
	sca_tdf::sca_in<double> sca_tdf_in_fin;		//< Input frequency
	sca_tdf::sc_out<bool> sc_out_fout;			//< Output divided frequency

	/**
	 * @param name_ Module name
	 * @param vcm_ Common mode voltage to detect edges in the input frequency.
	 * @param factor_ Divider factor
	 */
	sca_tdf_divider(sc_module_name name_,
				double vcm_,
				unsigned int factor_):
				sca_module(name_),
				vcm(vcm_),
				factor(factor_) {}
	
	/**
	 * Module initialization
	 */
	void init(void);

	/**
	 * Processing thread
	 */
	void processing(void);

};
