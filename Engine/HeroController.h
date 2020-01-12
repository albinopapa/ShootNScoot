#pragma once

#include "EntityController.h"
#include "Keyboard.h"
#include "Rect.h"

namespace sns
{
	class Hero;
	class Shield;
	class World;

	template<> struct EntityController<Hero>
	{
		static void Update(
			Hero& model,
			World& world,
			Keyboard const& kbd,
			float dt )noexcept;

		static void TakeDamage( Hero& model, float amount )noexcept;

		static RectF AABB( Hero const& model )noexcept;
		static float Damage( Hero const& model )noexcept;
		static float Health( Hero const& model )noexcept;
		static Vec2 const& Position( Hero const& model )noexcept;

	private:
		static void UpdateVelocity( Hero& model, Keyboard const& kbd )noexcept;
		static void ChangeWeapon( Hero& model, Keyboard const& kbd )noexcept;
	};
}
