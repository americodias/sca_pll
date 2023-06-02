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

/** @file sc_pfdetector.cpp
 *  @brief Phase Frequency Detector implementation
 *
 *  @author Americo Dias
 *  @date 06/02/2018
 */
#include "sc_pfdetector.h"

/**
 * Constructor implementation
 */
sc_pfdetector::sc_pfdetector(sc_module_name name_):
	sc_module(name_)
{
	SC_METHOD(sig_proc)
		sensitive << sc_in_fref.pos() << sc_in_fdiv.pos();
}

/**
 * Processing thread
 */
void sc_pfdetector::sig_proc(void) {
	static int state = 0;
	int next_state;

	switch(state) {
		case IDLE:
			if(sc_in_fref && sc_in_fdiv) {
				// Both fref and fdiv went up during last
				// timestep: keep IDLE
				next_state = IDLE;
			} else if(sc_in_fref) {
				sc_out_up.write(true);
				next_state = UP;
			} else if(sc_in_fdiv) {
				sc_out_dn.write(true);
				next_state = DN;
			}
			break;
		case UP:
			if(sc_in_fdiv) {
				sc_out_up.write(false);
				next_state = IDLE;
			}
			break;
		case DN:
			if(sc_in_fref) {
				sc_out_dn.write(false);
				next_state = IDLE;
			}
			break;
	}

	state = next_state;

}
