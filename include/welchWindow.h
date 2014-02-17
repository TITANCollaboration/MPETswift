#ifndef WELCHWINDOW_H
#define WELCHWINDOW_H

#include "IWindowing.h"

class welchWindow : public IWindowing {
	public:
		void applyWindow(WAVE* waveform);
};

#endif
