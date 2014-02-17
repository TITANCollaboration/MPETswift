#ifndef SMOOTHINGFACTORY_H
#define SMOOTHINGFACTORY_H

#include <memory>
#include <string>

#include "ISmoothing.h"
#include "movingAverage.h"
#include "smoothing2.h"
#include "noSmoothing.h"

using namespace std;

class smoothingFactory {
	public:
		static unique_ptr<ISmoothing> make_smoothing(string choice);
};

#endif
