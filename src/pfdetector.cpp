#include "pfdetector.h"

void pfdetector::sig_proc(void) {
	double diff = ref - fdbk;

	if(diff > 0) {
		UP.write(true);
		DN.write(false);
	} else if (diff < 0) {
		UP.write(false);
		DN.write(true); 
	} else {
		UP.write(false);
		DN.write(false);
	} 
}

