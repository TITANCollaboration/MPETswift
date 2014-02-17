#ifndef FFTGSL_H
#define FFTGSL_H

#include "IFFT.h"

#include <complex>

#include <gsl/gsl_errno.h>
#include <gsl/gsl_fft_complex.h>

using namespace std;

class FFTgsl : public IFFT {
	public:
		FFTgsl() {

		};

		~FFTgsl() {

		};

		void doForwardFFT(WAVE* waveform);
		void doBackwardFFT(WAVE* waveform);
};

#endif
