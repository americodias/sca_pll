#include "vcoscillator.h"

void vcoscillator::processing(void) {
	freq.write(((vc.read()/VCC)-0.5)*BW+F0);
	out.write( VGND+VGND*sin( sc_time_stamp().to_seconds()*((((vc.read()/VCC)-0.5)*BW+F0)*2.*M_PI))) ;
}

void vcoscillator::set_attributes(void) {
	out.set_timestep(TSTEP,sc_core::SC_SEC);
}