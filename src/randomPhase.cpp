#include "randomPhase.h"

#include <math.h>

double randomPhase::randPhase() {
	double f = (double)rand() / RAND_MAX;
	return (f * 2.0 - 1.0) * 0.5 * M_PI;
};

void randomPhase::phaseFunction(WAVE* waveform) {
	double phase;
	for(int i = 0; i < waveform->getN(); i++) {
		phase = randPhase();
		waveform->data[i] = waveform->data[i].real() * 
			complex<double>(cos(phase), sin(phase));
	}
};
