#include "BencherController.h"
#include "TimerController.h"
#include <sstream>
#include <algorithm>

void BencherController::Start( Bencher & model ) noexcept
{
	TimerController::Mark( model.ft );
}

bool BencherController::End( Bencher & model ) noexcept
{
	const float dt = TimerController::Mark( model.ft );
	model.min = std::min( dt, model.min );
	model.max = std::max( dt, model.max );
	model.mean += dt / model.nSamples;

	if( ++model.count >= model.nSamples )
	{
		// store results
		model.prevMin = model.min;
		model.prevMax = model.max;
		model.prevMean = model.mean;
		// reset bench state
		model.count = 0;
		model.min = std::numeric_limits<float>::max();
		model.max = 0.0f;
		model.mean = 0.0f;

		// signal results update
		return true;
	}
	return false;
}

std::wstring BencherController::String( Bencher const & model ) noexcept
{
	std::wostringstream oss;
	oss << L"Sample size: " << model.nSamples << std::endl
		<< L"Mean: " << model.prevMean * 1000.0f << L"ms" << std::endl
		<< L"Min: " << model.prevMin * 1000.0f << L"ms" << std::endl
		<< L"Max: " << model.prevMax * 1000.0f << L"ms" << std::endl;
	return oss.str();
}