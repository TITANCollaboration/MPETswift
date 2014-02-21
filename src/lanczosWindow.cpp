#include "lanczosWindow.h"

#include <math.h>
#include <boost/math/special_functions/sinc.hpp>

/* void lanczosWindow::applyWindow(WAVE* waveform) { */
/* 	double N = double(waveform->getN()); */
	
/* 	double k; */
/* 	for(int i = 0; i < waveform->getN(); i++) { */
/* 		k = double(i); */
/* 		waveform->data[i] *= (boost::math::sinc_pi(M_PI * (2. * k / (N - 1.) - 1.))); */
/* 	} */

void lanczosWindow::applyWindow(vector<complex<double> > &data) {
	unsigned int NN = data.size();
	double N = double(data.size());
	
	double k;
	for(int i = 0; i < NN; i++) {
		k = double(i);
		data[i] *= (boost::math::sinc_pi(M_PI * (2. * k / (N - 1.) - 1.)));
	}
};
/* }; */
