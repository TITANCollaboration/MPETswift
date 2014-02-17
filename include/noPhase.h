#ifndef NOPHASE_H
#define NOPHASE_H

#include "phaseStrategy.h"

class noPhase : public phaseStrategy {
	public:
		void phaseFunction(WAVE* waveform);
};

#endif
