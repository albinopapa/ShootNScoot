#include "Boss1Controller.h"
#include "Bosses.h"
#include "World.h"
#include <cassert>

namespace sns
{
	void Boss1Controller::Update( Boss1& model, World& world, float dt ) noexcept
	{
		const auto rect = ( model.aabb + model.position );
		switch( model.state )
		{
			case Boss1State::Attack:
				weapon.Update( model.weapon, dt );

				if( weapon.CanFire( model.weapon ) )
				{
					const auto missile_dir =
						( world.hero.position - model.position ).Normalize();

					weapon.Fire( 
						model.weapon,
						model.position, 
						missile_dir, 
						world, 
						AmmoOwner::Enemy 
					);

					++model.missile_count;
				}

				if( model.missile_count >= model.max_missiles )
					model.state = Boss1State::Regen;

				break;
			case Boss1State::Regen:
				if( model.regen_timer <= 0.f )
				{
					model.missile_count = 0;
					model.regen_timer = model.regen_delay;
					model.state = Boss1State::Attack;
				}
				break;
			case Boss1State::Idle:
			{
				if( rect.IsContainedBy( screenRect ) )
					model.state = Boss1State::Attack;
				break;
			}
			default:
				assert( false );
		}
	}

	void Boss1Controller::TakeDamage( Boss1& model, float amount ) noexcept
	{
		model.health -= amount;
	}

	float Boss1Controller::Damage( Boss1& model ) const noexcept
	{
		return Boss1::damage;
	}

	float Boss1Controller::Health( Boss1& model ) const noexcept
	{
		return model.health;
	}

	RectF Boss1Controller::AABB( Boss1& model ) const noexcept
	{
		return Boss1::aabb + model.position;
	}
}
