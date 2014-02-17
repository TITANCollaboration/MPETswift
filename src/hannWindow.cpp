#include "hannWindow.h"

#include <math.h>

void hannWindow::applyWindow(WAVE* waveform) {
	double N = double(waveform->getN());
	
	for(int i = 0; i < waveform->getN(); i++) {
		waveform->data[i] *= (pow(sin(M_PI * double(i) / N), 2.));
	}
};
