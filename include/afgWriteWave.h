#ifndef AFGWRTIREWAVE_H
#define AFGWRTIREWAVE_H

#include "wave.h"
#include "ScpiCommunicate.h"

/* #include <VISA/visa.h> */
#include <string>
#include <memory>

using namespace std;

class afgWriteWave {
	public:
		afgWriteWave() {
			maxSampleRate = 250000000; // Samples/sec
			/* _afgAddress = "TCPIP0::mpetswift.triumf.ca::inst0::INSTR"; */
			_arbName = "swift";
			_amplitude = 10.0; // 1.0 Vpp
			_outputLoad = 50;
			_device = unique_ptr<scpiCommunicate>(new scpiCommunicate());
		};

		void write(WAVE* waveform);
		void setAfgAddress(string afgAddress);
		void setArbName(string arbName);
		void setAmplitude(double amplitude);
		void setOutputLoad(int outputLoad);
		void setSampleRate(int N, double tExcite);
		/* void clearAfg(ViSession oMIO); */
		/* void resetAfg(ViSession oMIO); */
		/* void clearVolatileMemory(ViSession oMIO); */
		/* void swapBytesAfg(ViSession oMIO); */
		int buildAfgSwiftCommand(WAVE* waveform, char*& dataCommand);

	public:
		/* string _afgAddress; */
		unique_ptr<scpiCommunicate> _device;
		string _arbName;
		double _amplitude;
		int _outputLoad;
		int maxSampleRate;
		int sampleRate;
};

#endif
