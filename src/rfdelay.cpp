/*
 * rfdelay.cpp
 *
 *  Created on: 28. jan. 2018
 *      Author: ADias
 */

#include "rfdelay.h"


void rfdelay::prc_rfdelay(){
while(1){
wait(in.value_changed_event());
if(in==1)
{
b: while(out<vcc){
out=out+100e-3;
wait(6,SC_PS);
if(in==0){goto a;}
}
}
else
{
a: while(out>0){
out=out-100e-3;
wait(6,SC_PS);
if(in==1){goto b;}
}
}
}
}
