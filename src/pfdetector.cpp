#include "pfdetector.h"

void pfdetector::sig_proc(void) {
	double diff = ref - fdbk;

	if(diff > 0) {
		up_buf.write(true);
		dn_buf.write(false);
	} else if (diff < 0) {
		up_buf.write(false);
		dn_buf.write(true);
	} else {
		up_buf.write(false);
		dn_buf.write(false);
	}
}

