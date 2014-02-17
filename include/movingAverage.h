#ifndef MOVINGAVERAGE_H
#define MOVINGAVERAGE_H

#include "ISmoothing.h"

using namespace std;

class movingAverage : public ISmoothing {
	public:
		void smooth(WAVE* waveform, double df);
};

#endif
