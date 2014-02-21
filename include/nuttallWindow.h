#ifndef NUTTALLWINDOW_H
#define NUTTALLWINDOW_H

#include "IWindowing.h"

#include <complex>
#include <vector>

using namespace std;

class nuttallWindow : public IWindowing {
	public:
		void applyWindow(vector<complex<double> > &data);
		/* void applyWindow(WAVE* waveform); */
};

#endif
