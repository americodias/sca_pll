#define _USE_MATH_DEFINES
#include <math.h>
#include "vcoscillator.h"

using namespace std;

void vcoscillator::processing(void) {
	double frequency = kvo*vc.read() + fmin;
	double time = sc_time_stamp().to_seconds();

	//freq.write(((vc.read()/vcc)-0.5)*BW+F0);
	//out.write( VGND+VGND*sin( sc_time_stamp().to_seconds()*((((vc.read()/VCC)-0.5)*BW+F0)*2.*M_PI))) ;

	out.write((double)(vcm+vcm*sin(2*M_PI*frequency*time)));
	freq.write(frequency);
}

void vcoscillator::set_attributes(void) {
	out.set_timestep(tstep,sc_core::SC_SEC);
}
