#include "wave.h"

#include <math.h>
#include <iostream>

using namespace std;

void WAVE::reset() {
	data.clear();

	data.resize(N, complex<double>(0.0, 0.0));
}

void WAVE::setN(int NN) {
	if(NN < 0)
		throw -5;
	N = NN;
	reset();
}

int WAVE::getN() {
	return N;
}

/* template<typename T> */
void WAVE::printData(ostream& stream) {
	double mag;
	stream << "# frequency step = " << deltaFreq << endl;
	for(int i = 0; i < data.size(); i++) {
		mag = pow(data[i].real(), 2.) + pow(data[i].imag(), 2.);
		stream << i << "\t" << data[i].real() << "\t" << data[i].imag() << "\t" << mag << endl;
	}
}

void WAVE::scaleFreq() {
	for(int i = 0; i < _fstart.size(); i++) {
		/* _fstart[i] = _fstart[i] * tExcite; */
		/* _fend[i] = _fend[i] * tExcite; */
		_fstart[i] /= deltaFreq;
		_fend[i] /= deltaFreq;
	}
}

void WAVE::normalizeWaveform() {
	// find the maximum
	double max = 0.;
	for(int i = 0; i < getN(); i++) {
		if(max < fabs(data[i].real()))
			max = fabs(data[i].real());
	}

	// divide everything by the max
	for(int i = 0; i < getN(); i++) {
		data[i] /= max;
	}
};

void WAVE::setWindow(string windowing) {
	try {
		window = windowingFactory::make_window(windowing);
	} catch(...) {
		cerr << "Unknown windowing function " << windowing << "." << endl;
		cerr << "Aborting calculation." << endl;
		exit(1);
	}
};

void WAVE::doWindowing() {
	window->applyWindow(data);
};
