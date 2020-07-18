#pragma once

#include "Bullet.h"
#include "Vec2.h"
#include "Weapon.h"
#include "World.h"

class WeaponController
{
public:
	static void Update( Weapon& model, float dt )noexcept;
	static bool CanFire( Weapon& model )noexcept;
	static void Fire(
		Weapon& model,
		Vec2 const& position,
		Vec2 const& direction,
		World& world,
		AmmoOwner ammo_owner );
};
