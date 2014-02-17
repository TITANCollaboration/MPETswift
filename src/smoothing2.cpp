#include "smoothing2.h"

void smoothing2::smooth(WAVE* waveform, double df) {
	movAvg->smooth(waveform, df);
	movAvg->smooth(waveform, df);
};
