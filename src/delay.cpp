/*
 * delay.cpp
 *
 *  Created on: 28. jan. 2018
 *      Author: ADias
 */

#include "delay.h"

void delay::delay_thread(void){
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
