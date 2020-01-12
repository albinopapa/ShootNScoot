#include "Weapon.h"

namespace sns
{
	Weapon::Weapon( WeaponType type ) noexcept
		:
		variant( type )
	{}

	void Weapon::Update( float dt ) noexcept
	{
		if( state == State::Recharge )
		{
			fire_timer -= dt;
		}
	}

	void Weapon::Reset() noexcept
	{
		variant = Gun{};
		fire_timer = 0.f;
		state = State::Idle;
	}
}
