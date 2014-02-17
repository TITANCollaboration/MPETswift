#ifndef BLACKMANWINDOW_H
#define BLACKMANWINDOW_H

#include "IWindowing.h"

class blackmanWindow : public IWindowing {
	public:
		void applyWindow(WAVE* waveform);
};

#endif
