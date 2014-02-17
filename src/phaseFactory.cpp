#include "phaseFactory.h"

#include <ctype.h>

using namespace std;

unique_ptr<phaseStrategy> phaseFactory::make_phase(string choice) {
	for(int i = 0; i < choice.length(); i++) 
		choice[i] =  toupper(choice[i]);
	if(choice == "NOPHASE") {
		return unique_ptr<phaseStrategy>(new noPhase());
	} else if(choice == "RANDOMPHASE") {
		return unique_ptr<phaseStrategy>(new randomPhase());
	} else if(choice == "QUADRATICPHASE") {
		return unique_ptr<phaseStrategy>(new quadraticPhase());
	} else if(choice == "QUADRATICPHASECHEN") {
		return unique_ptr<phaseStrategy>(new quadraticPhaseChen());
	} else {
		throw -5;
	}

	return unique_ptr<phaseStrategy>();
};
