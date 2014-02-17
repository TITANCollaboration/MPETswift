#include "swiftFacade.h"

#include <stdlib.h>
#include <math.h>

using namespace std;

void swiftFacade::parseOptions(int argc, char* argv[]) {
	po::options_description desc = po::options_description("Allowed options");
	desc.add_options()
		("help", "produce help message")
		("fcent,f", po::value<double>(), "Set centre frequency")
		("fgap,g", po::value<double>(), "Set the frequency gap")
		("fclean,c", po::value<double>(), "Set the frequency cleaning width")
		("npoints,n", po::value<int>(), "Set the number of points in the waveform")
		("fdelta,d", po::value<double>()->default_value(1.), "Set the frequency step for the waveform")
		("phase,p", po::value<string>()->default_value("quadraticPhaseChen"), "Set the phase modulation function")
		("fbuild,b", po::value<string>()->default_value("simple"), "Set the frequency builder")
		("FFT", po::value<string>()->default_value("FFTW"), "Set the FFT algorithm")
		("window,w", po::value<string>()->default_value("plancktaperWindow"), "Set the windowing funciton")
		("smooth,s", po::value<string>()->default_value("smoothing2"), "Set the smoothing function")
		("lensmooth,l", po::value<double>()->default_value(0.), "Set the length of the smoothing window (Hz)")
		("texcite,t", po::value<double>()->default_value(0.02), "Set the excitation time")
		("voltage,V", po::value<double>()->default_value(1.0), "Set the excitation voltage")
		("afgname,a", po::value<string>()->default_value(""), "Name of waveform as stored on afg")
		("freqwave", po::value<string>()->default_value(""), "Name of output file for the initial frequency waveform")
		("twave", po::value<string>()->default_value(""), "Name of output file for the swift time-domain waveform")
		("twavewindowed", po::value<string>()->default_value(""), "Name of output file for the windowed swift time-domain waveform")
		("ifreqwave", po::value<string>()->default_value(""), "Name of output file for the zero-filled FFT waveform")
		;
	po::variables_map vm;
	po::store(po::parse_command_line(argc, argv, desc), vm);
	po::notify(vm);

	if(vm.count("help") || argc <= 1) {
		cout << desc << endl;
		exit(1);
	}

	// Get frequencies, and build f-wave form
	if(vm.count("fcent") && vm.count("fgap") && vm.count("fclean")) {
		setFreq(vm["fcent"].as<double>(), vm["fgap"].as<double>(), vm["fclean"].as<double>());
	} else {
		cerr << "Error: fcent, fgap and fclean must all be specified." << endl;
		cerr << "Abort." << endl;
		exit(1);
	}
	
	// Set the number of points in the waveform
	if(vm.count("npoints")) {
		setWaveN(vm["npoints"].as<int>());
	} else {
		cerr << "Number of points in the waveform must be specified." << endl;
		cerr << "Abort." << endl;
		exit(1);
	}

	// Set the deltaFreq
	waveform->deltaFreq = vm["fdelta"].as<double>();
	waveform->scaleFreq();

	// Set the phase modulation function
	setPhase(vm["phase"].as<string>());

	// Set the frequency builder
	setFreqBuild(vm["fbuild"].as<string>());

	// Set the FFT algorithm
	setFFT(vm["FFT"].as<string>());

	// Set the windowing function
	setWindowing(vm["window"].as<string>());

	// Set the smoothing function
	setSmoothing(vm["smooth"].as<string>());

	// Set the length of the smoothing function
	smoothingLength = vm["lensmooth"].as<double>();

	// The the excitation time
	waveform->tExcite = vm["texcite"].as<double>();
	waveform->tWaveform = vm["texcite"].as<double>();

	// Set the excitation amplitude
	amplitude = vm["voltage"].as<double>();

	// Set the name of the afg waveform in the afg memory
	setAfg(vm["afgname"].as<string>());

	// Set the output filename for the original waveform
	setOriginalFreqWavefromFile(vm["freqwave"].as<string>());

	// Set time-domain wavefrom output filename
	setTimeWaveformFile(vm["twave"].as<string>());

	setWindowedTimeWaveformFile(vm["twavewindowed"].as<string>());

	// Set zero-filled waveform output filename
	setZeroFillWaveformFile(vm["ifreqwave"].as<string>());
};

void swiftFacade::newWave() {
	waveform = unique_ptr<WAVE>(new WAVE);
};

void swiftFacade::setWaveN(int N) {
	waveform->setN(N);
};

void swiftFacade::setWaveDeltaFreq(double df) {
	waveform->deltaFreq = df;
};

void swiftFacade::setFreq(double cent, double gap, double width) {
	double halfGap = 0.5 * gap;
	vector<double> fstart, fend;
	fstart.push_back(cent - halfGap - width);
	fend.push_back(cent - halfGap);
	fstart.push_back(cent + halfGap);
	fend.push_back(cent + halfGap + width);

	waveform->_fstart = fstart;
	waveform->_fend = fend;
};

void swiftFacade::setFreqBuild(string fbuild) {
	try {
		makeFreq = FactoryBuildFreq::make_buildFreq(fbuild);
	} catch(...) {
		cerr << "Unknown frequency builder " << fbuild << "." << endl;
		cerr << "Aborting calculation." << endl;
		exit(1);
	}
};

void swiftFacade::setPhase(string phase) {
	try {
		phaseModulation = phaseFactory::make_phase(phase);
	} catch(...) {
		cerr << "Unknown phase modulation " << phase << "." << endl;
		cerr << "Aborting calculation." << endl;
		exit(1);
	}
};

void swiftFacade::setSmoothing(string smoothing) {
	try {
		smooth = smoothingFactory::make_smoothing(smoothing);
	} catch(...) {
		cerr << "Unknown smoothing function " << smoothing << "." << endl;
		cerr << "Aborting calculation." << endl;
		exit(1);
	}
};

void swiftFacade::setWindowing(string windowing) {
	try {
		window = windowingFactory::make_window(windowing);
	} catch(...) {
		cerr << "Unknown windowing function " << windowing << "." << endl;
		cerr << "Aborting calculation." << endl;
		exit(1);
	}
};

void swiftFacade::setFFT(string fft) {
	try {
		FFT = FFTFactory::make_FFT(fft);
	} catch(...) {
		cerr << "Unknown fft function " << fft << "." << endl;
		cerr << "Aborting calculation." << endl;
		exit(1);
	}
};

void swiftFacade::setAfg(string name) {
	/* afg = unique_ptr<afgWriteWave>(new afgWriteWave()); */
	if(name != "") {
		afg = unique_ptr<afgWriteWave>(new afgWriteWave());
		afg->setAmplitude(amplitude);
		afg->setArbName(name);
	}
	/* cout << name << endl; */
};

void swiftFacade::setOriginalFreqWavefromFile(string filename) {
	if(filename == "verbose") {
		/* OrgFreqWF = std::cout; */
	} else if(filename == "") {
		OrgFreqWF.close();
	} else {
		OrgFreqWF.open(filename, ofstream::trunc);
	};
};

void swiftFacade::doWriteOriginalFreqWaveform() {
	if(OrgFreqWF) {
		cout << "\t>>> Writing orginal waveform" << endl;
		waveform->printData(OrgFreqWF);
	}
};

void swiftFacade::setSmoothedFreqWaveformFile(string filename) {
	if(filename == "verbose") {
		/* SmoothFreqWF = std::cout; */
	} else if(filename == "") {
		SmoothFreqWF.close();
	} else {
		SmoothFreqWF.open(filename, ofstream::trunc);
	};
};

void swiftFacade::doWriteSmoothedFreqWaveform() {
	if(SmoothFreqWF) {
		cout << "\t>>> Writing Smoothed time-domain waveform" << endl;
		waveform->printData(SmoothFreqWF);
	}
};

void swiftFacade::setTimeWaveformFile(string filename) {
	if(filename == "verbose") {
		/* TimeWF = std::cout; */
	} else if(filename == "") {
		TimeWF.close();
	} else {
		TimeWF.open(filename, ofstream::trunc);
	};
};

void swiftFacade::doWriteTimeWaveform() {
	if(TimeWF) {
		cout << "\t>>> Writing time-domain waveform" << endl;
		waveform->printData(TimeWF);
	}
};

void swiftFacade::setWindowedTimeWaveformFile(string filename) {
	if(filename == "verbose") {
		/* WindTimeWF = std::cout; */
	} else if(filename == "") {
		WindTimeWF.close();
	} else {
		WindTimeWF.open(filename, ofstream::trunc);
	};
};

void swiftFacade::doWriteWindowedTimeWaveform() {
	if(WindTimeWF) {
		cout << "\t>>> Writing windowed time-domain waveform" << endl;
		waveform->printData(WindTimeWF);
	}
};

void swiftFacade::setZeroFillWaveformFile(string filename) {
	if(filename == "verbose") {
		/* ZFWF = std::cout; */
	} else if(filename == "") {
		ZFWF.close();
	} else {
		ZFWF.open(filename, ofstream::trunc);
	};
};

void swiftFacade::doWriteZeroFillWaveform() {
	if(ZFWF) {
		cout << "\t>>> Writing Zero-filled FFT waveform" << endl;
		waveform->printData(ZFWF);
	}
};

void swiftFacade::doBuildWave() {
	makeFreq->genFreq(waveform.get());
};

void swiftFacade::doPhaseModulation() {
	phaseModulation->phaseFunction(waveform.get());
};

void swiftFacade::doSmoothing() {
	double dfreq = smoothingLength;
	smooth->smooth(waveform.get(), dfreq);
};

void swiftFacade::doBackwardFFT() {
	FFT->doBackwardFFT(waveform.get());
};

void swiftFacade::doWindowing() {
	window->applyWindow(waveform.get());
};

void swiftFacade::doForwardFFT() {
	FFT->doForwardFFT(waveform.get());
};

void swiftFacade::doWriteAfg() {
	if(afg)
		afg->write(waveform.get());
	else
		cout << "\t>>> Not writing waveform to afg" << endl;
};

void swiftFacade::doWaveNormalization() {
	if(waveform)
		waveform->normalizeWaveform();
};
