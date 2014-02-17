#ifndef NUTTALLWINDOW_H
#define NUTTALLWINDOW_H

#include "IWindowing.h"

class nuttallWindow : public IWindowing {
	public:
		void applyWindow(WAVE* waveform);
};

#endif
