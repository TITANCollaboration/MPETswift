#ifndef FFTFACTORY_H
#define FFTFACTORY_H

#include <memory>

#include "IFFT.h"
#include "FFTW.h"
#include "FFTgsl.h"

using namespace std;

class FFTFactory {
	public:
		static unique_ptr<IFFT> make_FFT(string choice);
};

#endif
