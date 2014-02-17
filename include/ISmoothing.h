#ifndef ISMOOTHING_H
#define ISMOOTHING_H

#include "wave.h"

class ISmoothing {
	public:
		virtual ~ISmoothing() {};
		virtual void smooth(WAVE* waveform, double df) = 0;
};

#endif
