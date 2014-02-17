#ifndef FFTW_H
#define FFTW_H

#include "IFFT.h"

#include <complex>
#include <fftw3.h>

using namespace std;

class FFTW : public IFFT {
	public:
		FFTW() {
			
		};

		~FFTW() {
			/* if(ifft_zFill) */
			/* 	fftw_free(ifft_zFill); */
			/* if(fft_result) */
			/* 	fftw_free(fft_result); */
			/* if(ifft_result) */
			/* 	fftw_free(ifft_result); */
			/* fftw_destroy_plan(planForward); */
			/* fftw_destroy_plan(planBackward); */
		};

		void doForwardFFT(WAVE* waveform);
		void doBackwardFFT(WAVE* waveform);

	private:
		fftw_plan planForward, planBackward;
		fftw_complex *ifft_zFill, *fft_result, *ifft_result;
};

#endif
