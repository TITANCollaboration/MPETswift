#ifndef LANCZOSWINDOW_H
#define LANCZOSWINDOW_H

#include "IWindowing.h"

class lanczosWindow : public IWindowing {
	public:
		void applyWindow(WAVE* waveform);
};

#endif
