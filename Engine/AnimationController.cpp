#include "AnimationController.h"

void AnimationController::Update( Animation& model, float dt )noexcept
{
	model.curFrameTime += dt;
	while( model.curFrameTime >= model.holdTime )
	{
		Advance( model );
		model.curFrameTime -= model.holdTime;
	}
}

void AnimationController::Advance( Animation& model )noexcept
{
	if( ++model.iCurFrame >= model.frames.size() )
	{
		model.iCurFrame = 0;
	}
}
