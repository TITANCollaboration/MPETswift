#ifndef PHASEFACTORY_H
#define PHASEFACTORY_H

#include <memory>
#include <string>

#include "phaseStrategy.h"

#include "noPhase.h"
#include "randomPhase.h"
#include "quadraticPhase.h"
#include "quadraticPhaseChen.h"

using namespace std;

class phaseFactory {
	public:
		static unique_ptr<phaseStrategy> make_phase(string choice);
};

#endif
