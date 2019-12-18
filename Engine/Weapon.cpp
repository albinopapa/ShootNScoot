#include "Weapon.h"
#include "World.h"

namespace sns
{
	void Weapon::Update( float dt ) noexcept 
	{
		if( state == State::Recharge )
		{
			fire_timer -= dt;
			if( fire_timer <= 0.f )
			{
				state = State::Idle;
			}
		}
	}

	bool Weapon::CanFire( ) const noexcept {
		return state == State::Idle;
	}

	void Weapon::Fire( Vec2 const & position, Vec2 const & direction, World & world, Ammo::Owner ammo_owner ) noexcept {
		if( state == State::Idle )
		{
			std::visit( [ & ]( auto& weapon ) {
				using type = std::decay_t<decltype( weapon )>;
				using ammo_type = type::ammo_type;

				world.SpawnBullet( Ammo{ position, direction, ammo_type::max_energy, ammo_owner, ammo_type{} } );
				state = State::Recharge;

				fire_timer = type::fire_delay;
			}, variant );
		}
	}
	void Weapon::Reset() noexcept
	{
		variant = Gun{};
		fire_timer = 0.f;
		state = State::Idle;
	}
}
