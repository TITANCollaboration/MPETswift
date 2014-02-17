#include "FFTgsl.h"

#include <vector>

void FFTgsl::doForwardFFT(WAVE* waveform) {
	int n = 2 * waveform->getN();
	vector<double> data(2 * n, 0.); // use a vector so we don't run out of space on the stack

	for(int i = 0; i < waveform->getN(); i++) {
		data[2 * i] = waveform->data[i].real();
		data[2 * i + 1] = waveform->data[i].imag();
	}

	gsl_fft_complex_wavetable * wavetable = gsl_fft_complex_wavetable_alloc(n);
	gsl_fft_complex_workspace * workspace = gsl_fft_complex_workspace_alloc(n);
	
	gsl_fft_complex_forward(&data[0], 1, n, wavetable, workspace);

	waveform->setN(n);
	double scale = double(n) * 0.5;
	for(int i = 0; i < n; i++) {
		waveform->data[i] = complex<double>(data[2 * i] / scale, data[2 * i + 1] / scale);
	}

	gsl_fft_complex_wavetable_free (wavetable);
	gsl_fft_complex_workspace_free (workspace);
};

void FFTgsl::doBackwardFFT(WAVE* waveform) {
	int n = waveform->getN();
	vector<double> data(2 * n, 0.); // use a vector so we don't run out of space on the stack

	for(int i = 0; i < waveform->getN(); i++) {
		data[2 * i] = waveform->data[i].real();
		data[2 * i + 1] = waveform->data[i].imag();
	}

	gsl_fft_complex_wavetable * wavetable = gsl_fft_complex_wavetable_alloc(n);
	gsl_fft_complex_workspace * workspace = gsl_fft_complex_workspace_alloc(n);
	
	gsl_fft_complex_backward(&data[0], 1, n, wavetable, workspace);

	for(int i = 0; i < n; i++) {
		if(i < n / 2) {
			waveform->data[i + n / 2] = complex<double>(data[2 * i], data[2 * i + 1]);
			/* std::cout << i << " " << i + SIZE / 2 << std::endl; */
		} else if(i >= n / 2) {
			waveform->data[i - n / 2] = complex<double>(data[2 * i], data[2 * i + 1]);
			/* std::cout << i << " " << i - SIZE / 2 << std::endl; */
		}
	}

	gsl_fft_complex_wavetable_free (wavetable);
	gsl_fft_complex_workspace_free (workspace);
};
