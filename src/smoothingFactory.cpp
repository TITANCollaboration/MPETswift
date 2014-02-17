#include "smoothingFactory.h"

unique_ptr<ISmoothing> smoothingFactory::make_smoothing(string choice) {
	if(choice == "movingAverage")
		return unique_ptr<ISmoothing>(new movingAverage());
	if(choice == "smoothing2")
		return unique_ptr<ISmoothing>(new smoothing2());
	if(choice == "noSmoothing")
		return unique_ptr<ISmoothing>(new noSmoothing());
	else
		throw -5;

	return unique_ptr<ISmoothing>();
};
