#include "BossController.h"
#include "Bosses.h"
#include "ChiliMath.h"
#include "HeroController.h"
#include "World.h"
#include "WeaponController.h"
#include <cassert>

namespace sns
{
	void EntityController<Boss>::Update( Boss& model, World& world, float dt ) noexcept
	{
		std::visit( [ & ]( auto& boss )
		{
			Update( boss, world, model, dt );
		}, model.variant );
	}

	void EntityController<Boss>::TakeDamage( Boss& model, float amount ) noexcept
	{
		model.health -= amount;
	}

	float EntityController<Boss>::Damage( Boss const& model )noexcept
	{
		return std::visit( [ & ]( auto const& boss )
		{
			return std::decay_t<decltype( boss )>::damage;
		}, model.variant );
	}

	float EntityController<Boss>::Health( Boss const& model )noexcept
	{
		return model.health;
	}

	RectF EntityController<Boss>::AABB( Boss const& model )noexcept
	{
		return std::visit( [ & ]( auto const& boss )
		{
			return std::decay_t<decltype( boss )>::aabb + model.position;
		}, model.variant );
	}

	void EntityController<Boss>::Update( Boss1& model, World& world, Boss& parent, float dt )noexcept
	{
		switch( model.state )
		{
			case Boss1State::Attack:
				WeaponController::Update( model.weapon, dt );

				if( WeaponController::CanFire( model.weapon ) )
				{
					const auto missile_dir =
						( EntityController<Hero>::Position( world.hero ) - parent.position ).Normalize();

					WeaponController::Fire(
						model.weapon,
						parent.position,
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
				if( ( model.aabb + parent.position ).IsContainedBy( screenRect ) )
					model.state = Boss1State::Attack;
				break;
			}
			default:
				assert( false );
		}
	}

	void EntityController<Boss>::Update( Boss2& model, World& world, Boss& parent, float dt )noexcept
	{
		switch( model.state )
		{
			case Boss2::State::Idle:
			{
				if( ( model.aabb + parent.position ).IsContainedBy( screenRect ) )
				{
					model.state = Boss2::State::Signaling;
				}
				break;
			}
			case Boss2::State::Signaling:
			{
				if( model.signal_timer <= 0.f )
				{
					model.signal_timer = model.signal_delay;
					model.state = Boss2::State::Ramming;
				}
				else
				{
					model.waypoint = HeroController::Position( world.hero );

					parent.direction = ( model.waypoint - parent.position ).Normalize();;

					parent.angle = lerp(
						parent.angle, 
						std::atan2( parent.direction.y, parent.direction.x ),
						model.signal_timer / model.signal_delay 
					);
				}
				break;
			}
			case Boss2::State::Ramming:
			{
				if( ( model.waypoint - parent.position ).LengthSq() < 4.f )
				{
					model.state = Boss2::State::Recharging;
				}
				break;
			}
			case Boss2::State::Recharging:
			{
				if( model.cool_down_timer <= 0.f )
				{
					model.cool_down_timer = model.cool_down_delay;
					model.state = Boss2::State::Signaling;
				}
				break;
			}
			default:
				break;
		}
	}

	void EntityController<Boss>::Update( Boss3& model, World& world, Boss& parent, float dt )noexcept
	{}
	void EntityController<Boss>::Update( Boss4& model, World& world, Boss& parent, float dt )noexcept
	{}
	void EntityController<Boss>::Update( Boss5& model, World& world, Boss& parent, float dt )noexcept
	{}
	void EntityController<Boss>::Update( Boss6& model, World& world, Boss& parent, float dt )noexcept
	{}
	void EntityController<Boss>::Update( Boss7& model, World& world, Boss& parent, float dt )noexcept
	{}
	void EntityController<Boss>::Update( Boss8& model, World& world, Boss& parent, float dt )noexcept
	{}
	void EntityController<Boss>::Update( Boss9& model, World& world, Boss& parent, float dt )noexcept
	{}
	void EntityController<Boss>::Update( Boss10& model, World& world, Boss& parent, float dt )noexcept
	{}
}
