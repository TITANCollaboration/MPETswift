#include "welchWindow.h"

#include <math.h>

void welchWindow::applyWindow(WAVE* waveform) {
	double N = double(waveform->getN());
	
	double k;
	for(int i = 0; i < waveform->getN(); i++) {
		k = double(i);
		waveform->data[i] *= 1. - pow((k - (N - 1.) * 0.5) / (0.5 * (N + 1)), 2.0);
	}
};
