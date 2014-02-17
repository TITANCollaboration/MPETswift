#include <iostream>
#include <vector>
#include <fstream>
#include <memory>

#include "wave.h"
#include "buildFreq.h"
#include "phaseFactory.h"
#include "FFTFactory.h"
#include "smoothingFactory.h"
#include "windowingFactory.h"
#include "afgWriteWave.h"

using namespace std;

void my_print(WAVE* waveform) {
	cout << "wavefrom N = " << waveform->getN() << endl;
};

int main() {
	unique_ptr<afgWriteWave> afg = unique_ptr<afgWriteWave>(new afgWriteWave());

	unique_ptr<WAVE> waveform = unique_ptr<WAVE>(new WAVE());

	vector<double> fstart, fend;
	fstart.push_back(1451680.0-10000.-900.); 
	fstart.push_back(1451680.0+900.0);
	fend.push_back(1451680-900.); 
	fend.push_back(1451680+900.+10000.);
	/* fstart.push_back(10.); */
	/* fend.push_back(20.); */
	waveform->_fstart = fstart;
	waveform->_fend = fend;
	waveform->tExcite = 0.01;
	waveform->tWaveform = 0.01;
	waveform->deltaFreq = 10.;
	waveform->scaleFreq();

	unique_ptr<buildFreq> makeFreq = FactoryBuildFreq::make_buildFreq("simple");

	/* unique_ptr<phaseStrategy> rp = phaseFactory::make_phase("noPhase"); */
	/* unique_ptr<phaseStrategy> rp = phaseFactory::make_phase("quadraticPhase"); */
	unique_ptr<phaseStrategy> rp = phaseFactory::make_phase("quadraticPhaseChen");
	/* unique_ptr<phaseStrategy> rp = phaseFactory::make_phase("randomPhase"); */

	/* unique_ptr<ISmoothing> sm = smoothingFactory::make_smoothing("noSmoothing"); */
	/* unique_ptr<ISmoothing> sm = smoothingFactory::make_smoothing("movingAverage"); */
	unique_ptr<ISmoothing> sm = smoothingFactory::make_smoothing("smoothing2");

	unique_ptr<IFFT> FFT = FFTFactory::make_FFT("FFTW");

	/* unique_ptr<IWindowing> wind = windowingFactory::make_window("noWindow"); */
	/* unique_ptr<IWindowing> wind = windowingFactory::make_window("hammingWindow"); */
	/* unique_ptr<IWindowing> wind = windowingFactory::make_window("hannWindow"); */
	/* unique_ptr<IWindowing> wind = windowingFactory::make_window("blackmanWindow"); */
	/* unique_ptr<IWindowing> wind = windowingFactory::make_window("nuttallWindow"); */
	unique_ptr<IWindowing> wind = windowingFactory::make_window("plancktaperWindow");
	/* unique_ptr<IWindowing> wind = windowingFactory::make_window("pandgWindow"); */

	ofstream file("outputTest.dat", ofstream::trunc);

	int size;
	for(;;) {
		cout << "Set waveform size (Exit(0)): " << endl;
		cin >> size;

		if( size == 0)
			break;

		try {
			waveform->setN(size);
			my_print(waveform.get());

			makeFreq->genFreq(waveform.get());
			sm->smooth(waveform.get(), 30.);
			rp->phaseFunction(waveform.get());
			FFT->doBackwardFFT(waveform.get());
			wind->applyWindow(waveform.get());

			afg->write(waveform.get());
			
			FFT->doForwardFFT(waveform.get());

			/* waveform->printData(std::cout); */
			waveform->printData(file);
		} catch(...) {
			cout << "Invalid size. Try again" << endl;
		}
	}
	file.close();

	return 0;
}
