#include "ScpiCommunicate.h"

void scpiCommunicate::openDeviceStream(string host, string port) {
	// connect boost iostream to host and port
	_deviceStream.connect(host, port);
	if(!_deviceStream) {
		cerr << "ScpiCommunicate: Error. Could not connect to device at " << host << ":" << port << endl;
		cerr << "Abort" << endl;
		exit(1);
	}
	// set host and port
	_host = host;
	_port = port;
};

void scpiCommunicate::writeToDevice(string cmd) {
	_deviceStream << cmd;
};

string scpiCommunicate::queryDevice(string cmd) {
	writeToDevice(cmd);
	string response = readFromDevice();
	return response;
};
		
string scpiCommunicate::readFromDevice() {
	string response;
	getline(_deviceStream, response);
	return response;
};

bool scpiCommunicate::deviceError() {
	_deviceStream << "SYST:ERR?\n";
	string response;
	getline(_deviceStream, response);
	cout << response << endl;
	if(response.compare(_noErrorString) == 0)
		return false;
	else {
		cerr << "scpiCommunicate: Error " << response << endl;
		cerr << "Abort" << endl;
		/* return false; */
		exit(0);
	}
	// Should never get here.
	return true;
};

void scpiCommunicate::writeBuffer(char* long_cmd, int length) {
	// Since char arrays are generally '\0' terminated, we need
	// a special function to write the waveform data to the AFG.
	// The binary data will probably be a 'zero' in the first point,
	// so to ensure that the whole char array is written, we need
	// to tell the iostream how many bytes to write.
	_deviceStream.write(long_cmd, length);
};
