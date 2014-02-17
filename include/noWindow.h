#ifndef NOWINDOW_H
#define NOWINDOW_H

#include "IWindowing.h"

class noWindow : public IWindowing {
	public:
		void applyWindow(WAVE* waveform);
};

#endif
