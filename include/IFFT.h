#ifndef IFFT_H
#define IFFT_H

#include "wave.h"

using namespace std;

class IFFT {
	public:
		virtual ~IFFT() {};
		virtual void doForwardFFT(WAVE* waveform) = 0;
		virtual void doBackwardFFT(WAVE* waveform) = 0;
};

#endif
