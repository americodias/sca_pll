/** @file sca_tdf_divider.cpp
 *  @brief Frequency divider module implementation
 *
 *  @author Americo Dias
 *  @date 06/02/2018
 */
#include "sca_tdf_divider.h"

/**
 * Module initialization
 */
void sca_tdf_divider::init(void) {
	state=false;
	state_div=false;
	counter=0;
}

/**
 * Processing thread
 */
void sca_tdf_divider::processing(void) { // our workhorse method

	if(sca_tdf_in_fin.read() >= vcm and state == false) {
		state = true;
		counter += 2;
		if(counter >= factor) {
			counter = 0;
			state_div = !state_div;
		}
	} 
	else if(sca_tdf_in_fin.read() < vcm){
		state = false;
	}
	sc_out_fout.write(state_div);
}
