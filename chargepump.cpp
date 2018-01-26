#include "chargepump.h"

void chargepump::init(void) {
	tau = 1.0/(2.0*M_PI*fp);
	tn1 = 0;
}

void chargepump::processing(void) {
	double vds;
	double charge = 0,
		   discharge = 0,
		   mismatch = 0;
	
	if(vc>min&&vc<max) {
		charge=currentup;
		discharge=-currentdw;
		mismatch=charge+discharge;
	}
	else if(vc<min) {
		vds=vc;
		charge=currentup;
		discharge=-20/9.0*currentdw*vds+100/81.0*currentdw*vds*vds;
		mismatch=charge+discharge;
   }
   else if(vc>max) {
	   vds=VCC-vc;
	   charge=20/9.0*currentup*vds-100/81.0*currentup*vds*vds;
	   discharge=-currentdw;
	   mismatch=charge+discharge;
   }

   if(UP.read() && !DN.read()) {
	   iout=charge;
   }
   else if(!UP.read() && DN.read()) {
	   iout=discharge;
   }
   else if(!UP.read() && !DN.read()) {
	   iout=-leakage;
   }
	else if(UP.read() && DN.read()) {
	   iout=mismatch;
   }
   
	double tn = sc_time_stamp().to_seconds();
	double dt = tn - tn1;

	vc = vc + (iout*tau + iout*dt)/cap;
	tn1 = tn;

	out.write(vc);
}



void chargepump::set_attributes(void) {
	out.set_timestep(TSTEP,sc_core::SC_SEC);
}
