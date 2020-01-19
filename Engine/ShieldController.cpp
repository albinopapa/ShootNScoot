#include "ShieldController.h"
#include "Shield.h"

namespace sns
{
	void ShieldController::Update( Shield& model, Vec2 const& position, float dt ) noexcept
	{
		switch( model.state )
		{
			case Shield::State::Recharging:
			{
				model.health += ( dt * Shield::recharge_rate );
				if( model.health >= Shield::recharge_max )
				{
					model.state = Shield::State::Full;
					model.health = Shield::recharge_max;
				}
				else if( model.health <= 0.f )
				{
					model.state = Shield::State::Depleted;
					model.health = 0.f;
				}
				break;
			}
			case Shield::State::Depleted:
			{
				model.recharge_delay_timer -= dt;
				if( model.recharge_delay_timer <= 0.f )
				{
					model.state = Shield::State::Recharging;
					model.recharge_delay_timer = Shield::recharge_delay;
				}
				break;
			}
			case Shield::State::Full:
			{
				if( model.health < Shield::recharge_max )
					model.state = Shield::State::Recharging;
				else if( model.health <= 0.f )
					model.state = Shield::State::Depleted;
			}
		}
	}

	void ShieldController::TakeDamage( Shield& model, float amount ) noexcept
	{
		switch( model.state )
		{
			case Shield::State::Full:
			case Shield::State::Recharging:
			{
				model.health -= amount;
			}
		}
	}
	RectF ShieldController::AABB( Shield const& model, Vec2 position )noexcept
	{
		return RectF{ -Shield::radius, -Shield::radius, Shield::radius, Shield::radius } + position;
	}
	float ShieldController::Health( Shield const& model )noexcept
	{
		return model.health;
	}
	void ShieldController::Reset( Shield & model ) noexcept
	{
		model.health = 100.f;
		model.state = Shield::State::Full;
		model.recharge_delay_timer = 0.f;
	}
}
