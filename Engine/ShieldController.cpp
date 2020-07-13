#include "ShieldController.h"
#include "Shield.h"

namespace sns
{
	void ShieldController::Update( Shield& model, Vec2 const& position, float dt ) noexcept
	{
		constexpr auto rect =
			RectF{ -Shield::radius,-Shield::radius,Shield::radius,Shield::radius };

		switch( model.state )
		{
			case ShieldState::Recharging:
			{
				if( model.health >= Shield::recharge_max )
				{
					model.state = ShieldState::Full;
					model.health = Shield::recharge_max;
				}
				else if( model.health <= 0.f )
				{
					model.state = ShieldState::Depleted;
					model.health = 0.f;
				}
				break;
			}
			case ShieldState::Depleted:
			{
				if( model.recharge_delay_timer <= 0.f )
				{
					model.state = ShieldState::Recharging;
					model.recharge_delay_timer = Shield::recharge_delay;
				}
				break;
			}
			case ShieldState::Full:
			{
				if( model.health < Shield::recharge_max )
					model.state = ShieldState::Recharging;
				else if( model.health <= 0.f )
					model.state = ShieldState::Depleted;
			}
		}
	}

	void ShieldController::TakeDamage( Shield& model, float amount ) noexcept
	{
		switch( model.state )
		{
			case ShieldState::Full:
			case ShieldState::Recharging:
			{
				model.health -= amount;
			}
		}
	}
	RectF ShieldController::AABB( Shield& model, Vec2 position ) const noexcept
	{
		return RectF{ -Shield::radius, -Shield::radius, Shield::radius, Shield::radius } + position;
	}
	float ShieldController::Health( Shield& model ) const noexcept
	{
		return model.health;
	}
}
