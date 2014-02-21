#ifndef IWINDOWING_H
#define IWINDOWING_H

/* #include "wave.h" */

#include <vector>
#include <complex>

using namespace std;

class IWindowing {
	public:
		virtual ~IWindowing() {};
		/* virtual void applyWindow(WAVE* waveform) = 0; */
		virtual void applyWindow(vector<complex<double> > &data) = 0;
};

#endif
