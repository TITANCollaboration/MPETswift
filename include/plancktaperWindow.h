#ifndef PLANCKTAPERWINDOW_H
#define PLANCKTAPERWINDOW_H

#include "IWindowing.h"

class plancktaperWindow : public IWindowing {
	public:
		void applyWindow(WAVE* waveform);
		double Zm(double f, double N, double eta);
		double Zp(double f, double N, double eta);
};

#endif
