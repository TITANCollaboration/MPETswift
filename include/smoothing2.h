#ifndef SMOOTHING2_H
#define SMOOTHING2_H

#include "ISmoothing.h"
#include "movingAverage.h"

#include <memory>

using namespace std;

class smoothing2 : public ISmoothing {
	public:
		smoothing2() {
			movAvg = unique_ptr<ISmoothing>(new movingAverage);
		};
		void smooth(WAVE* waveform, double df);
	
	private:
		unique_ptr<ISmoothing> movAvg;
};

#endif
