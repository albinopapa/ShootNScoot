#pragma once
#include "Weapon.h"
#include "Vec2.h"
#include "Ammo.h"
#include "World.h"
	class WeaponController
	{
	public:
		void Update( Weapon& model, float dt );
		bool CanFire( Weapon& model )const noexcept;
		void Fire( 
			Weapon& model,
			Vec2 const & position, 
			Vec2 const & direction,
			World& world, 
			AmmoOwner ammo_owner );
	};