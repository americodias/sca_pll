/** @file sc_delay.cpp
 *  @brief Delay module implementation
 *
 *  @author Americo Dias
 *  @date 06/02/2018
 */
#include "sc_delay.h"

/**
 * Processing thread implementation
 */
void sc_delay::delay_thread(void){
	while(1){
		wait(in.value_changed_event());
		bool in_tmp = in;
		if(in_tmp!=out)
		{
			wait(in_tmp==true?tr:tf,sc_core::SC_SEC);
			if(in==in_tmp)
				out=!out;
		}
	}
}
