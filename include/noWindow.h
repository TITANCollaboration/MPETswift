#ifndef NOWINDOW_H
#define NOWINDOW_H

#include "IWindowing.h"

#include <complex>
#include <vector>

using namespace std;

class noWindow : public IWindowing {
	public:
		void applyWindow(vector<complex<double> > &data);
		/* void applyWindow(WAVE* waveform); */
};

#endif
