#include "nuttallWindow.h"

#include <math.h>

/* void nuttallWindow::applyWindow(WAVE* waveform) { */
/* 	double N = double(waveform->getN()); */

/* 	double a0 = 0.355768; */
/* 	double a1 = 0.487396; */
/* 	double a2 = 0.144232; */
/* 	double a3 = 0.012604; */
	
/* 	double argterm; */
/* 	for(int i = 0; i < waveform->getN(); i++) { */
/* 		argterm = M_PI * double(i) / (N - 1.); */
/* 		waveform->data[i] *= (a0 - a1 * cos(2. * argterm) + a2 * cos(4. * argterm) - a3 * cos(6. * argterm)); */
/* 	} */
/* }; */

void nuttallWindow::applyWindow(vector<complex<double> > &data) {
	unsigned int NN = data.size();
	double N = double(NN);

	double a0 = 0.355768;
	double a1 = 0.487396;
	double a2 = 0.144232;
	double a3 = 0.012604;
	
	double argterm;
	for(int i = 0; i < NN; i++) {
		argterm = M_PI * double(i) / (N - 1.);
		data[i] *= (a0 - a1 * cos(2. * argterm) + a2 * cos(4. * argterm) - a3 * cos(6. * argterm));
	}
};
