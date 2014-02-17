#ifndef RANDOMPHASE_H
#define RANDOMPHASE_H

#include <stdlib.h>
#include <time.h>

#include "phaseStrategy.h"

using namespace std;

class randomPhase : public phaseStrategy {
	public:
		randomPhase() {
			srand(time(NULL));
		}
		void phaseFunction(WAVE* waveform);
	private:
		double randPhase();
};

#endif
