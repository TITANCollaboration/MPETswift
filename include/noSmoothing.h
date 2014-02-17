#ifndef NOSMOOTHING_H
#define NOSMOOTHING_H

#include "ISmoothing.h"

class noSmoothing : public ISmoothing {
	public:
		void smooth(WAVE* waveform, double df);
};

#endif
