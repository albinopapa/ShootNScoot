#include "FrameTimer.h"
#include "TimerController.h"

float TimerController::Mark( FrameTimer & model ) noexcept
{
	const auto old = model.last;
	model.last = std::chrono::steady_clock::now();
	const auto frameTime = std::chrono::duration<float>( model.last - old );
	return frameTime.count();
}
