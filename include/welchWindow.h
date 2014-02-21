#ifndef WELCHWINDOW_H
#define WELCHWINDOW_H

#include "IWindowing.h"

#include <complex>
#include <vector>

using namespace std;

class welchWindow : public IWindowing {
	public:
		void applyWindow(vector<complex<double> > &data);
		/* void applyWindow(WAVE* waveform); */
};

#endif
