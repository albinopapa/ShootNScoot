#include "AnimationController.h"
#include "CharacterController.h"
#include "Character.h"

void CharacterController::SetDirection( Character & model, const Vec2 & dir ) noexcept
{
	if( dir.x > 0.0f )
	{
		model.iCurSequence = Character::Sequence::WalkingRight;
	}
	else if( dir.x < 0.0f )
	{
		model.iCurSequence = Character::Sequence::WalkingLeft;
	}
	else if( dir.y < 0.0f )
	{
		model.iCurSequence = Character::Sequence::WalkingUp;
	}
	else if( dir.y > 0.0f )
	{
		model.iCurSequence = Character::Sequence::WalkingDown;
	}
	else
	{
		if( model.vel.x > 0.0f )
		{
			model.iCurSequence = Character::Sequence::StandingRight;
		}
		else if( model.vel.x < 0.0f )
		{
			model.iCurSequence = Character::Sequence::StandingLeft;
		}
		else if( model.vel.y < 0.0f )
		{
			model.iCurSequence = Character::Sequence::StandingUp;
		}
		else if( model.vel.y > 0.0f )
		{
			model.iCurSequence = Character::Sequence::StandingDown;
		}
	}
	model.vel = dir * model.speed;
}

void CharacterController::Update( Character & model, float dt ) noexcept
{
	model.pos += model.vel * dt;
	AnimationController::Update( model.animations[ ( int )model.iCurSequence ], dt );

	// update effect time if active
	if( model.effectActive )
	{
		model.effectTime += dt;
		// deactivate effect if duration exceeded
		if( model.effectTime >= Character::effectDuration )
		{
			model.effectActive = false;
		}
	}
}

void CharacterController::ActivateEffect( Character & model ) noexcept
{
	model.effectActive = true;
	model.effectTime = 0.0f;
}
