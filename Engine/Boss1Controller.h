#pragma once

#include "Bosses.h"
#include "Rect.h"
#include "WeaponController.h"
#include "World.h"

class Boss1Controller
{
public:
	void Update( Boss1& model, World& world_model, float dt )noexcept;

	void TakeDamage( Boss1& model, float amount )noexcept;
	RectF AABB( Boss1& model )const noexcept;
	float Damage( Boss1& model )const noexcept;
	float Health( Boss1& model )const noexcept;
private:
	WeaponController weapon;
};
