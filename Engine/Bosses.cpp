#include "Bosses.h"
#include "Graphics.h"
#include "World.h"
#include <cassert>

namespace sns
{
	Boss1::Boss1()noexcept
	{
		weapon.variant = MissileLauncher{};
	}
	void Boss1::Update( float dt, World & world )
	{
		switch( state )
		{
			case State::Attack:
				weapon.Update( dt );
				if( weapon.CanFire() )
				{
					const auto missile_dir =
						( world.hero.position - position ).Normalize();
					weapon.Fire( position, missile_dir, world, Ammo::Owner::Enemy );
					++missile_count;
				}

				if( missile_count >= max_missiles )
				{
					state = State::Regen;
				}

				break;
			case State::Regen:
				regen_timer -= dt;
				if( regen_timer <= 0.f )
				{
					missile_count = 0;
					regen_timer = regen_delay;
					state = State::Attack;
				}
				break;
			case State::Idle:
				position += ( direction * ( Boss1::speed * dt ) );
				if( ( aabb + position ).IsContainedBy( screenRect ) )
					state = State::Attack;
				break;
			default:
				assert( false );
		}
	}

	void Boss1::TakeDamage( float amount ) noexcept
	{
		health -= amount;
	}

	void Boss1::Draw( Surface const& sprite, Graphics & gfx ) const noexcept
	{
		gfx.DrawSprite(
			int( position.x ),
			int( position.y ),
			sprite,
			SpriteEffect::Chroma{ Colors::Magenta }
		);
	}

	void Boss1::Reset() noexcept
	{
		position = { screenRect.Center().x, -32.f };
		direction = { 0.f, -1.f };
		state = State::Idle;
		regen_timer = regen_delay;
		health = max_health;
		missile_count = 0;
	}
}
