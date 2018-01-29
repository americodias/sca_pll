#include "chargepump.h"

void chargepump::processing(void) {

	double charge = 0,
			discharge = 0,
			mismatch = 0,
			i = 0;


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

	if(up && !dn) {
		i = charge;
	}
	else if(!up && dn) {
		i = discharge;
	}
	else if(!up && !dn) {
		i = -current_leak;
	}
	else if(up && dn) {
		i = mismatch;
	}

	if((vc>vcc && i>0) || (vc<0 && i<0)) {
		i=0;
	}

	iout = i;
}

void chargepump::set_attributes(void) {
	iout.set_timestep(tstep,sc_core::SC_SEC);
	//vc.set_timestep(tstep,sc_core::SC_SEC);
	iout.set_delay(1);
}

chargepump::chargepump(sc_module_name name_,
		double tstep_,
		double vcc_,
		double current_up_,
		double current_dn_,
		double current_leak_,
		double mosfet_vth_):
		sca_module(name_) {

	tstep=tstep_;
	vcc=vcc_;
	current_up=current_up_;
	current_dn=current_dn_;
	current_leak=current_leak_;
	mosfet_vth=mosfet_vth_;
	mosfet_vp=vcc_-mosfet_vth_;
	mosfet_vn=mosfet_vth_;

}

