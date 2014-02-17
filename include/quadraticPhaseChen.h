#ifndef QUADRATICPHASECHEN_H
#define QUADRATICPHASECHEN_H

#include "phaseStrategy.h"

using namespace std;

class quadraticPhaseChen : public phaseStrategy {
	public:
		void phaseFunction(WAVE* waveform);
		double totalPhase(double f, double A, double B, double fs);
};

#endif
