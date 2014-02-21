#ifndef HANNWINDOW_H
#define HANNWINDOW_H

#include "IWindowing.h"

#include <complex>
#include <vector>

using namespace std;

class hannWindow : public IWindowing {
	public:
		void applyWindow(vector<complex<double> > &data);
		/* void applyWindow(WAVE* waveform); */
};

#endif
