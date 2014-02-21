#ifndef BLACKMANWINDOW_H
#define BLACKMANWINDOW_H

#include "IWindowing.h"

#include <complex>
#include <vector>

using namespace std;

class blackmanWindow : public IWindowing {
	public:
		void applyWindow(vector<complex<double> > &data);
		/* void applyWindow(WAVE* waveform); */
};

#endif
