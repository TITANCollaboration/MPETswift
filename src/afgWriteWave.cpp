#include "afgWriteWave.h"

#include <iostream>
#include <iomanip>
#include <unistd.h>

using namespace std;

void afgWriteWave::write(WAVE* waveform) {
	/* int status; */

	/* // Open VISA sessions */
	/* ViSession resourceManager; */
	/* ViSession afgIO; */

	/* // Open */ 
	/* status = viOpenDefaultRM(&resourceManager); */
	/* if(status < VI_SUCCESS) { */
	/* 	/1* exit(EXIT_FAILURE); *1/ */
	/* 	throw -5; */
	/* } */

	/* char instrAdd[_afgAddress.size()]; */
	/* strcpy(instrAdd, _afgAddress.c_str()); */
	/* status = viOpen(resourceManager, instrAdd, VI_NULL, VI_NULL, &afgIO); */
	/* if(status < VI_SUCCESS){ */
	/* 	/1* exit(EXIT_FAILURE); *1/ */
	/* 	throw -5; */
	/* } */

	setSampleRate(waveform->getN(), waveform->tWaveform);

	/* clearAfg(afgIO); */
	/* resetAfg(afgIO); */
	/* clearVolatileMemory(afgIO); */
	_device->writeToDevice("*CLS\n");
	_device->writeToDevice("*RST\n");
	_device->writeToDevice("SOUR:DATA:VOL:CLE\n");

	/* swapBytesAfg(afgIO); */
	_device->writeToDevice("FORM:BORD SWAP\n");

	/* waveform->normalizeWaveform(); */

	/* viPrintf(afgIO,ViString("TRIGger1:SOUR EXT\n")); // set trigger, choice {IMMediate|EXT|TIMer|BUS} */
	/* viPrintf(afgIO,ViString("SOUR1:BURSt:MODE TRIG\n")); // choice of {TRIGgered|GATed} */
	/* viPrintf(afgIO,ViString("SOUR1:BURSt:NCYCles 1\n")); // number of cycles {<a number>|INF|MIN|MAX} */
	/* viPrintf(afgIO,ViString("SOUR1:BURSt:PHASE 0\n"));   // phase, prevents error for N > 1 MS */
	/* viPrintf(afgIO,ViString("SOUR1:BURSt:STATe ON\n"));  // enable burst mode */
	_device->writeToDevice("TRIGger1:SOUR EXT\n");
	_device->writeToDevice("SOUR1:BURSt:MODE TRIG\n");
	_device->writeToDevice("SOUR1:BURSt:NCYCles 1\n");
	_device->writeToDevice("SOUR1:BURSt:PHASE 0\n");
	_device->writeToDevice("SOUR1:BURSt:PHASE 0\n");
	_device->writeToDevice("SOUR1:BURSt:STATe ON\n");
	
	//Set desired configuration.
	/* viPrintf(afgIO,ViString("SOURCE1:VOLT %f\n"), _amplitude); */
	/* viPrintf(afgIO,ViString("SOURCE1:VOLT:OFFSET %d\n"), 0); */
	/* viPrintf(afgIO,ViString("OUTPUT1:LOAD %d\n"), _outputLoad); */
	/* viPrintf(afgIO,ViString("FUNC:ARB:SRATE %d\n"), sampleRate); // set the sample rate */
	/* viPrintf(afgIO,ViString("FUNC ARB\n")); // turn on arb function */
	_device->writeToDevice("SOURCE1:VOLT %f\n", _amplitude);
	_device->writeToDevice("SOURCE1:VOLT:OFFSET %d\n", 0);
	_device->writeToDevice("OUTPUT1:LOAD %d\n", _outputLoad);
	_device->writeToDevice("FUNC:ARB:SRATE %d\n", sampleRate);
	_device->writeToDevice("FUNC ARB\n");

	//char *cmd = nullptr;
	char *cmd = NULL;
	int dataLength = buildAfgSwiftCommand(waveform, cmd);

	//int dataLength = strlen(cmd) + waveform->getN() * sizeof(float) + 1;

	/* viBufWrite(afgIO, ViBuf(cmd), dataLength, VI_NULL); */
	/* _device->writeToDevice(cmd); */
	cout << "\t>>> Writing waveform to afg" << endl;
	_device->writeBuffer(cmd, dataLength);

	// Check for errors
	char noErrString[256] = "+0,\"No error\"";
	char strResult[256];
	/* viQueryf(afgIO, ViString("SYST:ERR?\n"), ViString("%t"), &strResult); */
	sprintf(strResult, "%s", _device->queryDevice("SYST:ERR?\n").c_str());
	// Output if successful or not...
	if(!(strcmp(strResult,noErrString)))
	/* if(!(_device->deviceError())) */
	{
		printf("\t>>> Arbitrary wave downloaded without any error\n");
	} else {
		printf("\t>>> Error reported: %s\n", strResult);
	}

	// Change arb function to waveform
	/* viPrintf(afgIO, ViString("FUNC:ARB %s\n"), _arbName.c_str()); */
	_device->writeToDevice("FUNC:ARB %s\n", _arbName);

	// release the resources
	free(cmd);
	/* viClose(resourceManager); */
	/* viClose(afgIO); */
};

void afgWriteWave::setAfgAddress(string afgAddress) {
	/* _afgAddress = afgAddress; */
};

void afgWriteWave::setArbName(string arbName) {
	_arbName = arbName;
};

void afgWriteWave::setAmplitude(double amplitude) {
	_amplitude = amplitude;
};

void afgWriteWave::setOutputLoad(int outputLoad) {
	_outputLoad = outputLoad;
};

void afgWriteWave::setSampleRate(int N, double tExcite) {
	if (int(N/tExcite) < maxSampleRate){
		sampleRate = int(N/tExcite); //sample rate in Sa/sec
	} else {
		sampleRate = maxSampleRate;
	}
};

/* void afgWriteWave::clearAfg(ViSession afgIO) { */
/* 	char cmd[] = "*CLS\n"; */
/* 	viPrintf(afgIO, cmd); */
/* }; */

/* void afgWriteWave::resetAfg(ViSession afgIO) { */
/* 	char cmd[] = "*RST\n"; */
/* 	viPrintf(afgIO, cmd); */
/* }; */

/* void afgWriteWave::clearVolatileMemory(ViSession afgIO) { */
/* 	char cmd[] = "SOUR:DATA:VOL:CLE\n"; */
/* 	viPrintf(afgIO, cmd); */
/* }; */

/* void afgWriteWave::swapBytesAfg(ViSession afgIO) { */
/* 	// Make sure the AFG swaps the bits */
/* 	char cmd[] = "FORM:BORD SWAP\n"; */
/* 	ViUInt32 retCount; */
/* 	viBufWrite (afgIO, (ViBuf)cmd, (ViUInt32)strlen(cmd), &retCount); */
/* }; */

int afgWriteWave::buildAfgSwiftCommand(WAVE* waveform, char*& dataCommand) {
	int binaryDataLength = waveform->getN() * sizeof(float);
	
	char dataLenStr[10];
	sprintf(dataLenStr, "%d", binaryDataLength);
	char arbCommand[100];
	int offset = int(strlen(dataLenStr));
	sprintf(arbCommand, "DATA:ARB %s, #%d%s", _arbName.c_str(), offset, dataLenStr);

	// allocate memory for dataCommand. Include one extra char for "\n" to terminate the cstring
	offset = int(strlen(arbCommand));
	dataCommand = new char[binaryDataLength + offset + 1];

	// Copy the initial arb command to dataCommand
	memcpy(dataCommand, arbCommand, offset);

	// Copy the wave form into the dataCommand string
	float waveDataPoint;
	for(int i = 0; i < waveform->getN(); i++) {
		waveDataPoint = float(waveform->data[i].real()); // Convert double to float
		// Copy the float into the char array as binary data
		memcpy(dataCommand + offset + i * sizeof(float), &waveDataPoint, sizeof(float));
	}

	// put a "\n" at the end of the command
	memcpy(dataCommand+offset+binaryDataLength, "\n", sizeof(char));
	return binaryDataLength + offset + 1;
};
