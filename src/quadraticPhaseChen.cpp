#include <quadraticPhaseChen.h>

#include <math.h>
#include <complex>

using namespace std;

double quadraticPhaseChen::totalPhase(double f, double A, double B, double fs) {
	return A * (f - fs) + 0.5 * B * pow(f - fs, 2.0);
};

void quadraticPhaseChen::phaseFunction(WAVE* waveform) {
	double start, end;
	start = waveform->_fstart[0];
	end = waveform->_fend[waveform->_fend.size() - 1];

	double A = 0.5 * M_PI;
	double B = -M_PI / (end - start);

	double phase;
	for(int i = 0; i < waveform->getN(); i++) {
		phase = totalPhase(i, A, B, waveform->_fstart[0]);
		waveform->data[i] = waveform->data[i] * 
			complex<double>(cos(phase), sin(phase));
	}
};
