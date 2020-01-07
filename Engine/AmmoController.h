#pragma once

#include "Rect.h"

namespace sns
{
	class Ammo;

	class AmmoController
	{
	public:
		static void Update( Ammo& model, float dt )noexcept;
		static void TakeDamage( Ammo& model, float amount )noexcept;

		static float Damage( Ammo const& model )noexcept;
		static RectF AABB( Ammo const& model )noexcept;
		static bool IsAlive( Ammo const& model )noexcept;
	};
}