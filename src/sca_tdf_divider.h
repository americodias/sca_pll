/** @file sca_tdf_divider.h
 *  @brief Frequency divider module include file
 *
 *  @author Americo Dias
 *  @date 06/02/2018
 */
#pragma once

/** @cond */
#include "systemc-ams.h"
/** @endcond */

/**
 * Frequency divider module
 */
SCA_TDF_MODULE(sca_tdf_divider) {
private:
	// Private variables
	double vcm;
	unsigned int factor;

	bool state=false;
	bool state_div=false;
	unsigned long counter=0;
	
public:
	// Ports
	sca_tdf::sca_in<double> sca_tdf_in_fin;		//< Input frequency
	sca_tdf::sc_out<bool> sc_out_fout;			//< Output divided frequency

	/**
	 * @param name_ Module name
	 * @param vcm_ Common mode voltage to detect edges in the input frequency.
	 * @param factor_ Divider factor
	 */
	sca_tdf_divider(sc_module_name name_,
				double vcm_,
				double factor_):
				sca_module(name_),
				vcm(vcm_),
				factor(factor_) {}
	
	/**
	 * Module initialization
	 */
	void init(void);

	/**
	 * Processing thread
	 */
	void processing(void);

};
