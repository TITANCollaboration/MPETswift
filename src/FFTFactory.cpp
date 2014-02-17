#include "FFTFactory.h"

unique_ptr<IFFT> FFTFactory::make_FFT(string choice) {
	if(choice == "FFTW") {
		return unique_ptr<IFFT>(new FFTW());
	} else if (choice == "FFTgsl") {
		return unique_ptr<IFFT>(new FFTgsl());
	} else {
		throw -5;
	};

	return unique_ptr<IFFT>();
};
