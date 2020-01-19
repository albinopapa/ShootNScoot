#pragma once

#include "FrameTimer.h"
#include <limits>

class Bencher
{
private:
	friend class BencherController;

	FrameTimer ft;
	int count = 0;
	int nSamples = 5;
	float min = std::numeric_limits<float>::max();
	float max = 0.0f;
	float mean = 0.0f;
	float prevMin = std::numeric_limits<float>::signaling_NaN();
	float prevMax = std::numeric_limits<float>::signaling_NaN();
	float prevMean = std::numeric_limits<float>::signaling_NaN();
};