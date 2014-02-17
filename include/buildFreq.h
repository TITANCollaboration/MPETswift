#ifndef BUILDFREQ_H
#define BUILDFREQ_H

#include "wave.h"

#include <string.h>
#include <vector>
#include <memory>

using namespace std;

class buildFreq {
	public:
		virtual ~buildFreq(){};
		/* virtual void genFreq(WAVE* waveform, vector<double> v1, vector<double> v3) = 0; */
		virtual void genFreq(WAVE* waveform) = 0;
};

class simpleBuildFreq : public buildFreq {
	public:
		/* void genFreq(WAVE* waveform, vector<double> fstart, vector<double> fend); */
		void genFreq(WAVE* waveform);
};

class onesBuildFreq : public buildFreq {
	public:
		void genFreq(WAVE* waveform);
};

class FactoryBuildFreq {
	public:
		static unique_ptr<buildFreq> make_buildFreq(string choice);
};

#endif
