#pragma once

#include "Weapon.h"
#include "Vec2.h"

namespace sns
{
	class Weapon;
	class World;

	class WeaponController
	{
	public:
		static void Update( Weapon& model, float dt )noexcept;
		static bool CanFire( Weapon const& model )noexcept;
		static void Fire( 
			Weapon& model,
			Vec2 const & position, 
			Vec2 const & direction,
			World& world, 
			Ammo::Owner ammo_owner );
		template<typename T>
		static void SwitchWeapon( Weapon& model )noexcept
		{
			if( !std::holds_alternative<T>( model.variant ) ) model.variant = T{};
		}
		static void Reset( Weapon& model )noexcept;
	};
}