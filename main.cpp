#include <memory>
#include <fstream>
#include <string>

#include "swiftFacade.h"
#include "ScpiCommunicate.h"

using namespace std;

int main(int argc, char* argv[]) {
	unique_ptr<swiftFacade> swift = unique_ptr<swiftFacade>(new swiftFacade());

	// create a waveform object
	swift->newWave();

	// parse the commandline options
	swift->parseOptions(argc, argv);

	// build the desired frequency waveform
	swift->doBuildWave();
	swift->doWriteOriginalFreqWaveform();

	// smooth in frequency space
	swift->doSmoothing();
	swift->doPhaseModulation();

	// Do IFFT, window the time-domain signal, and normalize
	swift->doBackwardFFT();
	swift->doWindowing();
	swift->doWaveNormalization();
	
	// Write time-domain to the AFG
	swift->doWriteAfg();
	swift->doWriteTimeWaveform();

	// do FFT and write the waveform, only if the user wants it
	swift->doForwardFFT();
	swift->doWriteZeroFillWaveform();

	return 0;
}
