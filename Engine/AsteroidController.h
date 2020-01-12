#pragma once

#include "Asteroids.h"
#include "EntityController.h"
#include "Rect.h"

namespace sns
{
	template<> struct EntityController<Asteroid>
	{
		static void Update( Asteroid& model, float dt )noexcept;

		static void TakeDamage( Asteroid& model, float amount )noexcept;
		static void Reason( Asteroid& model, Asteroid::DeathReason reason )noexcept;

		static RectF AABB( Asteroid const& model )noexcept;
		static float Damage( Asteroid const& model )noexcept;
		static float Health( Asteroid const& model )noexcept;
		static bool IsBigAsteroid( Asteroid const& model )noexcept;
		static Vec2 const& Position( Asteroid const& model )noexcept;
		static Asteroid::DeathReason Reason( Asteroid const& model )noexcept;
		static int ScoreValue( Asteroid const& model )noexcept;
	};
}