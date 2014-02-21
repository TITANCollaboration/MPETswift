#include "plancktaperWindow.h"

#include <math.h>

double plancktaperWindow::Zp(double f, double j1, double j2) {
	if(f < 0.9) { //f is zero, so return 0.
		return 1.E100;
	}

	return (j2 - j1) / (f - j1) + (j2 - j1) / (f - j2);
};

double plancktaperWindow::Zm(double f, double j3, double j4) {
	return (j3 - j4) / (f - j3) + (j3 - j4) / (f - j4);
};

/* void plancktaperWindow::applyWindow(WAVE* waveform) { */
/* 	double N = double(waveform->getN()); */
/* 	double eta = 0.3; */

/* 	double k; */
/* 	/1* double lower = eta * (N - 1.); *1/ */
/* 	/1* double upper = (1. - eta) * (N - 1.); *1/ */
/* 	double j1 = 0; */
/* 	double j2 = eta * (N - 1.); */
/* 	double j3 = (1. - eta) * (N - 1.); */
/* 	double j4 = N - 1.; */
/* 	for(int i = 0; i < waveform->getN(); i++) { */
/* 		k = double(i); */
/* 		if(i == 0 || i == (N - 1)) { */
/* 			waveform->data[i] = 0.; */
/* 		} else if(k < j2) { */
/* 			/1* waveform->data[i] = 1. / (exp(Zp(k, N, eta)) + 1.); *1/ */
/* 			waveform->data[i] *= 1. / (exp(Zp(k, j1, j2)) + 1.); */
/* 		} else if(k >= j2 && k <= j3) { */
/* 			waveform->data[i] *= 1.; */
/* 		} else if(k > j3) { */
/* 			waveform->data[i] *= 1. / (exp(Zm(k, j3, j4)) + 1.); */
/* 		} */
/* 	} */
/* }; */

void plancktaperWindow::applyWindow(vector<complex<double> > &data) {
	unsigned int NN = data.size();
	double N = double(NN);
	double eta = 0.3;

	double k;
	/* double lower = eta * (N - 1.); */
	/* double upper = (1. - eta) * (N - 1.); */
	double j1 = 0;
	double j2 = eta * (N - 1.);
	double j3 = (1. - eta) * (N - 1.);
	double j4 = N - 1.;
	for(int i = 0; i < NN; i++) {
		k = double(i);
		if(i == 0 || i == (NN - 1)) {
			data[i] = 0.;
		} else if(k < j2) {
			/* waveform->data[i] = 1. / (exp(Zp(k, N, eta)) + 1.); */
			data[i] *= 1. / (exp(Zp(k, j1, j2)) + 1.);
		} else if(k >= j2 && k <= j3) {
			data[i] *= 1.;
		} else if(k > j3) {
			data[i] *= 1. / (exp(Zm(k, j3, j4)) + 1.);
		}
	}
};
