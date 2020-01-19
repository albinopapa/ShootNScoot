#pragma once

#include <chrono>

class FrameTimer
{
private:
	friend class TimerController;
	std::chrono::steady_clock::time_point last = std::chrono::steady_clock::now();
};
