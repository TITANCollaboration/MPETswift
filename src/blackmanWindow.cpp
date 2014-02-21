#include "blackmanWindow.h"

#include <math.h>

/* void blackmanWindow::applyWindow(WAVE* waveform) { */
/* 	double N = double(waveform->getN()); */
/* 	double alpha = 0.16; */
/* 	double a0 = (1 - alpha) / 2.0; */
/* 	double a1 = -0.5; */
/* 	double a2 = alpha / 2.0; */
	
/* 	double k; */
/* 	for(int i = 0; i < waveform->getN(); i++) { */
/* 		k = double(i); */
/* 		waveform->data[i] *= (a0 + a1*cos(2. * M_PI * k / N) + a2 * cos(4. * M_PI * k / N)); */
/* 	} */
/* }; */
void blackmanWindow::applyWindow(vector<complex<double> > &data) {
	/* double N = double(waveform->getN()); */
	unsigned int NN = data.size();
	double N = double(data.size());
	double alpha = 0.16;
	double a0 = (1 - alpha) / 2.0;
	double a1 = -0.5;
	double a2 = alpha / 2.0;
	
	double k;
	for(int i = 0; i < NN; i++) {
		k = double(i);
		data[i] *= (a0 + a1*cos(2. * M_PI * k / N) + a2 * cos(4. * M_PI * k / N));
	}
};
