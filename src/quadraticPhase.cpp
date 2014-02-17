#include "quadraticPhase.h"

#include <vector>
#include <iostream>
#include <math.h>

double quadraticPhase::phaseSolution(double f, double f0, double f1) {
	if(f < f0)
		return 0.;
	else if((f >= f0) && (f <= f1))
		return 0.5 * (f - f0) * (f - f0);
	else
		return 0.5 * (2.0 * f * (f1 - f0) + f0 * f0 - f1 * f1);
};

double quadraticPhase::totalPhase(double f, vector<double> fstart, vector<double> fend) {
	double tot = 0.;
	for(int i = 0; i < fstart.size(); i++) {
		tot += phaseSolution(f, fstart[i], fend[i]);
	}
	return tot;
};

double quadraticPhase::constant(double t0, double t1, vector<double> fstart, vector<double> fend) {
	double norm = 0.;

	for (int i = 0; i < fstart.size(); i++) {
		norm += fend[i] - fstart[i];
	}
	norm = (t1 - t0) / norm;
	return 2. * M_PI * norm;
};

void quadraticPhase::phaseFunction(WAVE* waveform) {
	vector<double> fstart = waveform->_fstart;
	vector<double> fend = waveform->_fend;

	for(int i = 0; i < fstart.size(); i++) {
		/* fstart[i] -= 50.; */
		/* fend[i] += 50.; */
		fstart[i] *= waveform->deltaFreq;
		fend[i] *= waveform->deltaFreq;
	}

	double phase;
	double t0, t1;
	t0 = 0.5 * (waveform->tWaveform - waveform->tExcite) - 0.5 * waveform->tWaveform;
	t1 = waveform->tWaveform - t0 - 0.5 * waveform->tWaveform;
	/* t0 *= waveform->deltaFreq; */
	/* t1 *= waveform->deltaFreq; */
	double norm = constant(t0, t1, fstart, fend);
	cout << norm << endl;

	double f;
	for(int i = 0; i < waveform->getN(); i++) {
		f = double(i) * waveform->deltaFreq;
		phase = norm * totalPhase(f, fstart, fend);
		phase += 2.0 * M_PI * t0 * (f - fstart[0]);
		waveform->data[i] = waveform->data[i].real() * 
			complex<double>(cos(phase), sin(phase));
		/* waveform->data[i] = phase; */
	}
};
