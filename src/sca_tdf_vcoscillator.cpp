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

/** @file sca_tdf_vcoscillator.cpp
 *  @brief Voltage Controlled Oscillator module implementation
 *
 *  @author Americo Dias
 *  @date 06/02/2018
 */
/** @cond */
#define _USE_MATH_DEFINES
#include <cmath>
/** @endcond */
#include "sca_tdf_vcoscillator.h"

using namespace std;

//double time0 = 0;
//double phi0 = 0;

double idtmod(double frequency, double time) {
	static double time0 = 0;
	static double phi0 = 0;

	double T { 1 / frequency };
	double phi = phi0 + 2*M_PI*(time-time0)/T;

	phi0 = phi = fmod(phi, 2*M_PI);		// Limit the phase between 0 and 2*pi
	time0 = time;						// Save the time for the next integration

	return phi;
}

/**
 * Set module attributes
 */
void sca_tdf_vcoscillator::set_attributes(void) {
	sca_tdf_out_fout.set_timestep(tstep,sc_core::SC_SEC);
}

/**
 * Processing thread
 */
void sca_tdf_vcoscillator::processing(void) {
	double frequency = kvo*sca_tdf_in_vctrl.read() + fmin;
	double time = sc_time_stamp().to_seconds();

	double phi=idtmod(frequency, time);

	sca_tdf_out_fout.write((double)(vcm+vcm*sin(phi)));
	sca_tdf_out_fout_freq.write(frequency);

}
