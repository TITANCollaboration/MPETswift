#ifndef WAVE_H
#define WAVE_H

#include <vector>
#include <complex.h>
#include <ostream>
#include <string>
#include <memory>

/* #include "phaseStrategy.h" */
/* #include "randomPhase.h" */
#include "windowingFactory.h"

using namespace std;

class WAVE {
	public:
		WAVE() {
			N = 0;
		}

		WAVE(int NN, double tEx, double tWave) {
			setN(NN);
			tExcite = tEx;
			tWaveform = tWave;
		}

		~WAVE(){};

		void reset();
		void setN(int NN);
		int getN();
		void printData(ostream& stream);

		void scaleFreq();

		void normalizeWaveform();

		void setWindow(string window);
		void doWindowing();

		vector<complex<double> > data;
		vector<double> _fstart, _fend;
		double tExcite, tWaveform;
		double deltaFreq;

		unique_ptr<IWindowing> window;

	private:
		int N;
};

#endif
