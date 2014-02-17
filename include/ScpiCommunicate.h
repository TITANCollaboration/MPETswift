#ifndef SCPICOMMUNICATE_H
#define SCPICOMMUNICATE_H

// This class opens a boost::ip::tcp::iostream to connect to the SCPI socket of a device.
// The commands 'writeToDevice', readFromDevice' and 'queryDevice' can be used to control
// the device.
//
// No checks are made that the commands sent are correct.
//
// No timeout check is made.
// i.e. If you try to read from the device, but the device has not output anything, the
// program will hang forever.

#include <stdio.h>
#include <stdarg.h>
#include <string>
#include <memory>
#include <iostream>

#include <boost/asio.hpp>
#include <boost/format.hpp>

using namespace std;
using boost::asio::ip::tcp;
using boost::format;

class scpiCommunicate {
	public:
		scpiCommunicate()  {
			_host = "mpetswift.triumf.ca";
			_port = "5025";
			openDeviceStream(_host, _port);
			_noErrorString = "+0,\"No error\"";
		};

		scpiCommunicate(string host, string port) {
			_host = host;
			_port = port;
			openDeviceStream(_host, _port);
			_noErrorString = "+0,\"No error\"";
		};

		// sprintf style function, only it returns a string.
		// Useful for constructing formatted commands for SCPI
		// communication.
		string devPrintf(format Format) {
			return Format.str();
		};
		template<typename ... Types>
		string devPrintf(const string fmtstr, Types ... rest) {
			format Format(fmtstr);
			return devPrintf(Format, rest...);
		};
		template<typename ... Types>
		string devPrintf(const char* fmtstr, Types ... rest) {
			format Format(fmtstr);
			return devPrintf(Format, rest...);
		};
		template<typename T, typename ... Types>
		string devPrintf(format Format, T t, Types ... rest) {
			Format % t;
			return devPrintf(Format, rest...);
		};

		void writeToDevice(string);
		// overload so that we can accpet printf sytle arguments
		// arg1 should be boost::format, string or char only.
		template<typename T, typename ... Types>
		void writeToDevice(T Format, Types ... rest) {
			string cmd = devPrintf(Format, rest...);
			writeToDevice(cmd);
		};
		void writeBuffer(char* long_cmd, int length);

		string queryDevice(string cmd);
		// overload so that we can accpet printf style arguments
		// arg1 should be boost::format, string or char only.
		template<typename T, typename ... Types>
		string queryDevice(T Format, Types ... rest) {
			string query = devPrintf(Format, rest...);
			return queryDevice(query);
		};

		string readFromDevice();
		bool deviceError();

	private:
		//const string _noErrorString = "+0,\"No error\"";
		string _noErrorString;
		string _host;
		string _port;
		boost::asio::ip::tcp::iostream _deviceStream;
		
		void openDeviceStream(string host, string port);
};

#endif
