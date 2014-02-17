#ifndef HANNWINDOW_H
#define HANNWINDOW_H

#include "IWindowing.h"

class hannWindow : public IWindowing {
	public:
		void applyWindow(WAVE* waveform);
};

#endif
