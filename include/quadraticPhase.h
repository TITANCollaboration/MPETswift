#ifndef QUADRATICPHASE_H
#define QUADRATICPHASE_H

#include "phaseStrategy.h"

using namespace std;

class quadraticPhase : public phaseStrategy {
	public:
		void phaseFunction(WAVE* waveform);
		double totalPhase(double f, vector<double> fstart, vector<double> fend);
		double constant(double t1, double t0, vector<double> fstart, vector<double> fend);
		double phaseSolution(double f, double f0, double f1);
};

#endif
