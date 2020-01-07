#pragma once

#include "Enumerations.h"
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
			AmmoOwner ammo_owner );
	};
}