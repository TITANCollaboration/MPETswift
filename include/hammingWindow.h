#ifndef HAMMINGWINDOW_H
#define HAMMINGWINDOW_H

#include "IWindowing.h"

class hammingWindow : public IWindowing {
	public:
		void applyWindow(WAVE* waveform);
};

#endif
