#pragma once

#include "Keyboard.h"
#include "ShieldController.h"
#include "WeaponController.h"

namespace sns
{
	class Hero;
	class World;

	class HeroController
	{
	public:
		void Update(
			Hero& model,
			World& world,
			Keyboard const& kbd,
			float dt )noexcept;

		void TakeDamage( Hero& model, float amount )noexcept;

		float Damage( Hero& model )const noexcept;
		RectF AABB( Hero& model )const noexcept;
		Shield& GetShield( Hero& model )noexcept;
		Shield const& GetShield( Hero& model )const noexcept;
		
	private:
		void UpdateVelocity( Hero& model, Keyboard const& kbd )noexcept;
		void ChangeWeapon( Hero& model, Keyboard const& kbd )noexcept;

	};
}
