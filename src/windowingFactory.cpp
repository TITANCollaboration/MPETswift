#include <windowingFactory.h>

using namespace std;

unique_ptr<IWindowing> windowingFactory::make_window(string choice) {
	if(choice == "noWindow") {
		return unique_ptr<IWindowing>(new noWindow());
	} else if(choice == "hammingWindow") {
		return unique_ptr<IWindowing>(new hammingWindow());
	} else if(choice == "hannWindow") {
		return unique_ptr<IWindowing>(new hannWindow());
	} else if(choice == "blackmanWindow") {
		return unique_ptr<IWindowing>(new blackmanWindow());
	} else if(choice == "nuttallWindow") {
		return unique_ptr<IWindowing>(new nuttallWindow());
	} else if(choice == "plancktaperWindow") {
		return unique_ptr<IWindowing>(new plancktaperWindow());
	} else if(choice == "lanczosWindow") {
		return unique_ptr<IWindowing>(new lanczosWindow());
	} else if(choice == "welchWindow") {
		return unique_ptr<IWindowing>(new welchWindow());
	} else {
		throw -5;
	}

	return unique_ptr<IWindowing>();
};
