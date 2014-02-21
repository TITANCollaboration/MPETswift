#ifndef PLANCKTAPERWINDOW_H
#define PLANCKTAPERWINDOW_H

#include "IWindowing.h"

#include <complex>
#include <vector>

using namespace std;

class plancktaperWindow : public IWindowing {
	public:
		void applyWindow(vector<complex<double> > &data);
		/* void applyWindow(WAVE* waveform); */
		double Zm(double f, double N, double eta);
		double Zp(double f, double N, double eta);
};

#endif
