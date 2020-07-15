#include "Bosses.h"
#include "Graphics.h"
#include "World.h"
#include <cassert>

Boss1::Boss1()noexcept
{
	weapon.variant = MissileLauncher{};
}
void Boss1::Update( float dt )
{
	switch( state )
	{
		case Boss1State::Attack:
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

void Boss1::Reset() noexcept
{
	position = { screenRect.Center().x, -32.f };
	direction = { 0.f, -1.f };
	state = Boss1State::Idle;
	regen_timer = regen_delay;
	health = max_health;
	missile_count = 0;
}
