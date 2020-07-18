#include "Weapon.h"

void Weapon::Update( float dt ) noexcept
{
	if( state == WeaponState::Recharge )
	{
		fire_timer -= dt;
	}
}

void Weapon::Reset() noexcept
{
	variant = Gun{};
	fire_timer = 0.f;
	state = WeaponState::Idle;
}
