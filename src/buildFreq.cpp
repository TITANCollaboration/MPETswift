#include "buildFreq.h"

#include <math.h>

using namespace std;

/* void simpleBuildFreq::genFreq(WAVE* waveform, vector<double> fstart, vector<double> fend) { */
void simpleBuildFreq::genFreq(WAVE* waveform) {
	// Check fstart and fend are the same length
	vector<double> fstart = waveform->_fstart;
	vector<double> fend = waveform->_fend;

	if(fstart.size() != fend.size())
		throw -1;
	
	// Check last fend is less than waveform.N
	/* if(waveform->getN() < fend[fend.size() - 1]) */
	/* 	throw -2; */
	
	// round start and end freq's to integers
	vector<int> _fstart, _fend;

	for(int i = 0; i < fstart.size(); i++) {
		_fstart.push_back(ceil(fstart[i]));
		_fend.push_back(floor(fend[i]));
	}

	// Reset waveform to zero
	waveform->reset();
	for(int i = 0; i < _fstart.size(); i++) {
		for(int j = 0; j < waveform->getN(); j++) {
			if(j >= _fstart[i] && j <= _fend[i])
				waveform->data[j] = 1.0;
		}
	}
};

void onesBuildFreq::genFreq(WAVE* waveform) {
	waveform->_fstart.clear();
	waveform->_fend.clear();
	for(int i = 0; i < waveform->getN(); i++) {
		waveform->data[i] = 1.0;
	}
};

unique_ptr<buildFreq> FactoryBuildFreq::make_buildFreq(string choice) {
	if(choice == "simple")
		return unique_ptr<buildFreq>(new simpleBuildFreq());
	else if(choice == "ones")
		return unique_ptr<buildFreq>(new onesBuildFreq());
	else
		throw -5;
	
	return unique_ptr<buildFreq>();
};
