#ifndef HAMMINGWINDOW_H
#define HAMMINGWINDOW_H

#include "IWindowing.h"

#include <complex>
#include <vector>

using namespace std;

class hammingWindow : public IWindowing {
	public:
		void applyWindow(vector<complex<double> > &data);
		/* void applyWindow(WAVE* waveform); */
};

#endif
