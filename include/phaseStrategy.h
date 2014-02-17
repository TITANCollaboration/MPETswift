#ifndef PHASESTRATEGY_H
#define PHASESTRATEGY_H

#include <vector>
#include "wave.h"

using namespace std;

class phaseStrategy {
	public:
		virtual ~phaseStrategy(){};
		virtual void phaseFunction(WAVE* waveform) = 0;
};

#endif
