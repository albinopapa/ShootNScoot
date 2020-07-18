#include "Shield.h"

void Shield::Update( float delta_time ) noexcept
{
	switch( state )
	{
		case ShieldState::Recharging:
			health += ( delta_time * Shield::recharge_rate );
			break;
		case ShieldState::Depleted:
			recharge_delay_timer -= delta_time;
			break;
	}
}
void Shield::Reset() noexcept
{
	health = 100.f;
	state = ShieldState::Full;
	recharge_delay_timer = 0.f;
}
