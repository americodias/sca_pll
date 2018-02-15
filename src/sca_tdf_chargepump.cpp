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
		double vdd_,
		double current_up_,
		double current_dn_,
		double current_leak_,
		double mosfet_vth_):
		sca_module(name_) {

	tstep=tstep_;
	vdd=vdd_;
	current_up=current_up_;
	current_dn=current_dn_;
	current_leak=current_leak_;
	mosfet_vth=mosfet_vth_;
	mosfet_vtp=mosfet_vth_;
	mosfet_vtn=vdd-mosfet_vth_;

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

	// Discharge (NMOS)
	if(sca_tdf_in_vcp>mosfet_vtn) {
		// Saturation
		discharge=-current_dn;
	} else {
		// Triode
		double vds = sca_tdf_in_vcp;
		discharge=-((2/(vdd-mosfet_vth))*current_dn*vds-(1/pow(vdd-mosfet_vth,2))*current_dn*pow(vds,2));
	}

	// Charge (PMOS)
	if(sca_tdf_in_vcp<mosfet_vtp) {
		// Saturation
		charge=current_up;
	} else {
		// Triode
		double vds = vdd-sca_tdf_in_vcp;;
		charge=(2/(vdd-mosfet_vth))*current_dn*vds-(1/pow(vdd-mosfet_vth,2))*current_dn*pow(vds,2);
	}

	mismatch=charge+discharge;


	/**
	 * Set the output current depending on the inputs state
	 * (up/down)
	 */
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

	/**
	 * Limit the output current if the loop filter input voltage
	 * is out of limits (V_CTRL < 0 || V_CTRL > vdd)
	 */
	if((sca_tdf_in_vcp>vdd && i>0) || (sca_tdf_in_vcp<0 && i<0)) {
		i=0;
	}

	sca_tdf_out_ictrl = i;
}
