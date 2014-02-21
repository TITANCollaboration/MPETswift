#include "hammingWindow.h"

#include <math.h>

/* void hammingWindow::applyWindow(WAVE* waveform) { */
/* 	double N = double(waveform->getN()); */
	
/* 	for(int i = 0; i < waveform->getN(); i++) { */
/* 		waveform->data[i] *= (0.54 - 0.46 * cos(2. * M_PI * double(i) / N)); */
/* 	} */
/* }; */

void hammingWindow::applyWindow(vector<complex<double> > &data) {
	unsigned int NN = data.size();
	double N = double(data.size());
	
	for(int i = 0; i < NN; i++) {
		data[i] *= (0.54 - 0.46 * cos(2. * M_PI * double(i) / N));
	}
};
