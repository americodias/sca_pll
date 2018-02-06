/** @file sca_tdf_chargepump.cpp
 *  @brief Charge Pump module implementation
 *
 *  @author Americo Dias
 *  @date 06/02/2018
 */
#include "sca_tdf_chargepump.h"

/**
 * Constructor implementation
 */
sca_tdf_chargepump::sca_tdf_chargepump(sc_module_name name_,
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

/**
 * Set module attributes
 */
void sca_tdf_chargepump::set_attributes(void) {
	sca_tdf_out_ictrl.set_timestep(tstep,sc_core::SC_SEC);
	sca_tdf_out_ictrl.set_delay(1);
}

/**
 * Processing thread
 */
void sca_tdf_chargepump::processing(void) {

	double charge = 0,
			discharge = 0,
			mismatch = 0,
			i = 0;


	if(sca_tdf_in_vctrl>mosfet_vn && sca_tdf_in_vctrl<mosfet_vp) {
		charge=current_up;
		discharge=-current_dn;
		mismatch=charge+discharge;
	}
	else if(sca_tdf_in_vctrl < mosfet_vn) {
		double vds = sca_tdf_in_vctrl;
		charge=current_up;
		discharge=-20/9.0*current_dn*vds+100/81.0*current_dn*vds*vds;
		mismatch=charge+discharge;
	}
	else if(sca_tdf_in_vctrl > mosfet_vp) {
		double vds = vcc-sca_tdf_in_vctrl;
		charge=20/9.0*current_up*vds-100/81.0*current_up*vds*vds;
		discharge=-current_dn;
		mismatch=charge+discharge;
	}

	if(sc_in_up && !sc_in_dn) {
		i = charge;
	}
	else if(!sc_in_up && sc_in_dn) {
		i = discharge;
	}
	else if(!sc_in_up && !sc_in_dn) {
		i = -current_leak;
	}
	else if(sc_in_up && sc_in_dn) {
		i = mismatch;
	}

	if((sca_tdf_in_vctrl>vcc && i>0) || (sca_tdf_in_vctrl<0 && i<0)) {
		i=0;
	}

	sca_tdf_out_ictrl = i;
}
