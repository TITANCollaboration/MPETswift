#ifndef SWIFTFACADE_H
#define SWIFTFACADE_H

#include <memory>
#include <fstream>
#include <ostream>
#include <iostream>
#include <vector>

#include "wave.h"
#include "buildFreq.h"
#include "phaseFactory.h"
#include "FFTFactory.h"
#include "smoothingFactory.h"
#include "windowingFactory.h"
#include "afgWriteWave.h"

#include <boost/program_options.hpp>

using namespace std;
namespace po = boost::program_options;

class swiftFacade {
	public:
		void parseOptions(int argc, char* argv[]);
		
		void newWave();
		void setWaveN(int N);
		void setWaveDeltaFreq(double df);
		void setFreq(double cent, double gap, double width);
		
		void setFreqBuild(string fbuild);
		void setPhase(string phase);
		void setSmoothing(string smoothing);
		void setWindowing(string windowing);
		void setFFT(string fft);
		void setAfg(string name);

		void setOriginalFreqWavefromFile(string filename);
		void setSmoothedFreqWaveformFile(string filename);
		void setTimeWaveformFile(string filename);
		void setWindowedTimeWaveformFile(string filename);
		void setZeroFillWaveformFile(string filename);

		void doBuildWave();
		void doPhaseModulation();
		void doSmoothing();
		void doBackwardFFT();
		void doWindowing();
		void doForwardFFT();
		void doWriteAfg();
		void doWaveNormalization();

		void doWriteOriginalFreqWaveform();
		void doWriteSmoothedFreqWaveform();
		void doWriteWindowedTimeWaveform();
		void doWriteTimeWaveform();
		void doWriteZeroFillWaveform();
	
		unique_ptr<WAVE> waveform;
		unique_ptr<buildFreq> makeFreq;
		unique_ptr<phaseStrategy> phaseModulation;
		unique_ptr<ISmoothing> smooth;
		/* unique_ptr<IWindowing> window; */
		unique_ptr<IFFT> FFT;
		unique_ptr<afgWriteWave> afg;

		ofstream OrgFreqWF;
		ofstream SmoothFreqWF;
		ofstream TimeWF;
		ofstream WindTimeWF;
		ofstream ZFWF;

		double smoothingLength;
		double texcite;
		double amplitude;
};

#endif
