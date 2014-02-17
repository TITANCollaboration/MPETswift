#include "movingAverage.h"

#include <algorithm>
#include <complex>
#include <vector>
#include <numeric>

using namespace std;

void movingAverage::smooth(WAVE* waveform, double df) {
	int n = int(df / waveform->deltaFreq);
	int dn = n / 2;

	// smoothing length is less than 1 point, so don't do anything
	if(dn < 1)
		return;

	vector<double> data;
	for(int i = 0; i < waveform->getN(); i++) {
		data.push_back(waveform->data[i].real());
	}

	waveform->setN(waveform->getN());

	int N = data.size();
	for(int i = 0; i < N; i++) {
		int lower = max(0, i - dn);
		int upper = min(N - 1, i + dn);
		double val = 0;
		val = accumulate(data.begin() + lower, data.begin() + upper, val);
		waveform->data[i] = val / (upper - lower);
	}
};
