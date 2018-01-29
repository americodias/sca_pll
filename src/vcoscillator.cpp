#define _USE_MATH_DEFINES
#include <cmath>
#include "vcoscillator.h"

using namespace std;

void vcoscillator::processing(void) {
	double frequency = kvo*vc.read() + fmin;
	double time = sc_time_stamp().to_seconds();

	out.write((double)(vcm+vcm*(double)sin(double(2*M_PI*frequency*time))));
	freq.write(frequency);
}

void vcoscillator::set_attributes(void) {
	out.set_timestep(tstep,sc_core::SC_SEC);
}
