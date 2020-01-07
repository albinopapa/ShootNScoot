#include "Bosses.h"
#include "Graphics.h"
#include "World.h"
#include <cassert>

namespace sns
{
	Boss::Boss( BossType type ) noexcept
		:
		variant( type )
	{
	}

	void Boss::Update( float dt )
	{
		std::visit( [ & ]( auto& boss )
		{
			boss.Update( position, direction, dt ); 
		}, variant );
	}

	void Boss::Reset() noexcept
	{
		position = { screenRect.Center().x, -32.f };
		direction = { 0.f, -1.f };
		variant = Boss1{};

		std::visit( [ & ]( auto& boss ) { health = boss.max_health; }, variant );
	}

	void Boss1::Update( Vec2& position, Vec2& direction, float dt )
	{
		switch( state )
		{
			case Boss1State::Attack:
				weapon.Update( dt );
				break;
			case Boss1State::Regen:
				regen_timer -= dt;
				break;
			case Boss1State::Idle:
				position += ( direction * ( Boss1::speed * dt ) );
				break;
			default:
				assert( false );
		}
	}

	void Boss2::Update( Vec2& position, Vec2& direction, float dt ) noexcept
	{
		switch( state )
		{
			case State::Signaling:
			{
				signal_timer -= dt;
				break;
			}
			case State::Ramming:
			{
				position += ( direction * ( speed * dt ) );
				break;
			}
			case State::Recharging:
			{
				cool_down_timer -= dt;
				break;
			}
			case State::Idle:
				position += ( Vec2{ 0.f, 1.f } *( speed * dt ) );
				break;
		}
	}

}
