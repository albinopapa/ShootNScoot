#pragma once

#include "Animation.h"
#include "SurfaceController.h"
#include "Vec2.h"

class Character
{
public:
	Character( const Vec2& pos );

private:
	enum class Sequence
	{
		WalkingLeft,
		WalkingRight,
		WalkingUp,
		WalkingDown,
		StandingLeft,
		StandingRight,
		StandingUp,
		StandingDown,
		Count
	};

private:
	friend class CharacterController;
	friend class CharacterView;

	Surface sprite = SurfaceController::CreateSurface( "Images\\link90x90.bmp" );
	std::vector<Animation> animations;
	Vec2 pos;
	Vec2 vel = { 0.0f,0.0f };
	Sequence iCurSequence = Sequence::StandingDown;
	float speed = 110.0f;
	float effectTime = 0.0f;
	bool effectActive = false;
	static constexpr float effectDuration = 0.045f;
};
