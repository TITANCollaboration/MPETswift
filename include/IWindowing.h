#ifndef IWINDOWING_H
#define IWINDOWING_H

#include "wave.h"

class IWindowing {
	public:
		virtual ~IWindowing() {};
		virtual void applyWindow(WAVE* waveform) = 0;
};

#endif
