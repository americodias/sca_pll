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

	sca_tdf_out_fout.write((double)(vcm+vcm*(double)sin(double(2*M_PI*frequency*time))));
	sca_tdf_out_fout_freq.write(frequency);
}
