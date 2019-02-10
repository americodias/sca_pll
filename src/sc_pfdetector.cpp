/** @file sc_pfdetector.cpp
 *  @brief Phase Frequency Detector implementation
 *
 *  @author Americo Dias
 *  @date 06/02/2018
 */
#include "sc_pfdetector.h"

/**
 * Constructor implementation
 */
sc_pfdetector::sc_pfdetector(sc_module_name name_):
	sc_module(name_)
{
	SC_METHOD(sig_proc)
		sensitive << sc_in_fref.pos() << sc_in_fdiv.pos();
}

/**
 * Processing thread
 */
void sc_pfdetector::sig_proc(void) {
	static int state = 0;
	int next_state;

	switch(state) {
		case IDLE:
			if(sc_in_fref && sc_in_fdiv) {
				// Both fref and fdiv went up during last
				// timestep: keep IDLE
				next_state = IDLE;
			} else if(sc_in_fref) {
				sc_out_up.write(true);
				next_state = UP;
			} else if(sc_in_fdiv) {
				sc_out_dn.write(true);
				next_state = DN;
			}
			break;
		case UP:
			if(sc_in_fdiv) {
				sc_out_up.write(false);
				next_state = IDLE;
			}
			break;
		case DN:
			if(sc_in_fref) {
				sc_out_dn.write(false);
				next_state = IDLE;
			}
			break;
	}

	state = next_state;

}
