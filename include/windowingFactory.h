#ifndef WINDOWINGFACTORY_H
#define WINDOWINGFACTORY_H

#include <memory>
#include <string>

#include "IWindowing.h"

#include "noWindow.h"
#include "hammingWindow.h"
#include "hannWindow.h"
#include "blackmanWindow.h"
#include "nuttallWindow.h"
#include "plancktaperWindow.h"
#include "lanczosWindow.h"
#include "welchWindow.h"

using namespace std;

class windowingFactory {
	public:
		static unique_ptr<IWindowing> make_window(string choice);
};

#endif
