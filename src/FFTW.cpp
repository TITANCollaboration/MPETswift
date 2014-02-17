#include "FFTW.h"
#include <iostream>

void FFTW::doForwardFFT(WAVE* waveform) {
	int SIZE = waveform->getN();
	int NSIZE = SIZE * 2;
	fft_result = (fftw_complex*)fftw_malloc(sizeof(fftw_complex) * NSIZE);
	ifft_zFill = (fftw_complex*)fftw_malloc(sizeof(fftw_complex) * NSIZE);

	planForward = fftw_plan_dft_1d(NSIZE, ifft_zFill, fft_result, FFTW_FORWARD, FFTW_ESTIMATE);

	for(int i = 0; i < NSIZE; i++) {
		if(i < SIZE) {
			ifft_zFill[i][0] = waveform->data[i].real();
			ifft_zFill[i][1] = waveform->data[i].imag();
		} else if(i >= SIZE) {
			ifft_zFill[i][0] = 0.;
			ifft_zFill[i][1] = 0.;
		}
	}

	fftw_execute(planForward);

	waveform->setN(NSIZE);
	double scale = double(NSIZE) * 0.5;
	for(int i = 0; i < NSIZE; i++) {
		//waveform->data[NSIZE - i] = complex<double>(fft_result[i][0] / scale, fft_result[i][1] / scale);
		waveform->data[i] = complex<double>(fft_result[i][0] / scale, fft_result[i][1] / scale);
	}

	// Free resource
	fftw_free(fft_result);
	fftw_free(ifft_zFill);
	fftw_destroy_plan(planForward);
};

void FFTW::doBackwardFFT(WAVE* waveform) {
	int SIZE = waveform->getN();

	fftw_complex* data = (fftw_complex*) fftw_malloc(sizeof(fftw_complex) * SIZE);
	ifft_result = (fftw_complex*)fftw_malloc(sizeof(fftw_complex) * SIZE);
	
	planBackward = fftw_plan_dft_1d(SIZE, data, ifft_result, FFTW_BACKWARD, FFTW_ESTIMATE);

	for(int i = 0; i < waveform->getN(); i++) {
		data[i][0] = waveform->data[i].real();
		data[i][1] = waveform->data[i].imag();
	}

	fftw_execute(planBackward);

	for(int i = 0; i < SIZE; i++) {
		if(i < SIZE / 2) {
			waveform->data[i + SIZE / 2] = complex<double>(ifft_result[i][0], ifft_result[i][1]);
			/* std::cout << i << " " << i + SIZE / 2 << std::endl; */
		} else if(i >= SIZE / 2) {
			waveform->data[i - SIZE / 2] = complex<double>(ifft_result[i][0], ifft_result[i][1]);
			/* std::cout << i << " " << i - SIZE / 2 << std::endl; */
		}
		/* waveform->data[i] = complex<double>(ifft_result[i][0], ifft_result[i][1]); */
	}

	// Free resources
	fftw_free(data);
	fftw_free(ifft_result);
	fftw_destroy_plan(planBackward);
};
