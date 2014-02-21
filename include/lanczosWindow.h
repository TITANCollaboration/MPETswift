#ifndef LANCZOSWINDOW_H
#define LANCZOSWINDOW_H

#include "IWindowing.h"

#include <complex>
#include <vector>

using namespace std;

class lanczosWindow : public IWindowing {
	public:
		void applyWindow(vector<complex<double> > &data);
		/* void applyWindow(WAVE* waveform); */
};

#endif
