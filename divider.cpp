#include "divider.h"

void divider::init(void) {
	state=false;
	state_div=false;
	counter=0;
}


void divider::processing(void) { // our workhorse method

	if(in.read() >= VGND and state == false) {
		state = true;
		counter += 2;
		if(counter >= factor) {
			counter = 0;
			state_div = !state_div;
		}
	} 
	else if(in.read() < VGND){
		state = false;
	}
	out.write(state_div);
}

