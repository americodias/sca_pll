#ifndef CONTROLM_H_
#define CONTROLM_H_

#include "systemc-ams.h"

SCA_TDF_MODULE(controlm) {
private:
	double tstep;
	double vcc;

public:
	sca_tdf::sca_in<double> iin;
	sca_tdf::sca_in<double> vc;
	sca_tdf::sca_out<double> iout;

	controlm(sc_module_name name_,
				double tstep_,
				double vcc_):
				sca_module(name_),
				tstep(tstep_),
				vcc(vcc_) {}

	void init(void);
	void processing(void);
	void set_attributes(void);
};

#endif /* CONTROLM_H_ */
