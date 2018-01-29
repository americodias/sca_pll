#include "chargepump.h"

void chargepump::processing(void) {

	double charge = 0,
		   discharge = 0,
		   mismatch = 0,
		   sw_threshold = vcc/2;
	
	if(vc>mosfet_vn && vc<mosfet_vp) {
		charge=current_up;
		discharge=-current_dn;
		mismatch=charge+discharge;
	}
	else if(vc < mosfet_vn) {
		double vds = vc;
		charge=current_up;
		discharge=-20/9.0*current_dn*vds+100/81.0*current_dn*vds*vds;
		mismatch=charge+discharge;
   }
   else if(vc > mosfet_vp) {
	   double vds = vcc-vc;
	   charge=20/9.0*current_up*vds-100/81.0*current_up*vds*vds;
	   discharge=-current_dn;
	   mismatch=charge+discharge;
   }

   if(UP.read() > sw_threshold && DN.read() < sw_threshold ) {
	   out=charge;
   }
   else if(UP.read() < sw_threshold && DN.read() > sw_threshold) {
	   out=discharge;
   }
   else if(UP.read() < sw_threshold && DN.read() < sw_threshold) {
	   out=-current_leak;
   }
	else if(UP.read() > sw_threshold && DN.read() > sw_threshold) {
	   out=mismatch;
   }
   
}

void chargepump::set_attributes(void) {
	out.set_timestep(tstep,sc_core::SC_SEC);
	out.set_delay(1);
}

