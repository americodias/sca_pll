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

/** @file sca_tdf_divider.cpp
 *  @brief Frequency divider module implementation
 *
 *  @author Americo Dias
 *  @date 06/02/2018
 */
#include "sca_tdf_divider.h"

/**
 * Module initialization
 */
void sca_tdf_divider::init(void) {
	state=false;
	state_div=false;
	counter=0;
}

/**
 * Processing thread
 */
void sca_tdf_divider::processing(void) { // our workhorse method

	if(sca_tdf_in_fin.read() >= vcm and state == false) {
		state = true;
		counter += 2;
		if(counter >= factor) {
			counter = 0;
			state_div = !state_div;
		}
	} 
	else if(sca_tdf_in_fin.read() < vcm){
		state = false;
	}
	sc_out_fout.write(state_div);
}
