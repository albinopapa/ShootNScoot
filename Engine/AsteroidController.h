#pragma once

#include "Enumerations.h"
#include "Rect.h"

namespace sns
{
	class Asteroid;

	class AsteroidController
	{
	public:
		static void Update( Asteroid& model, float dt )noexcept;

		static void TakeDamage( Asteroid& model, float amount )noexcept;
		static void Reason( Asteroid& model, AsteroidDeathReason reason )noexcept;

		static RectF AABB( Asteroid const& model )noexcept;
		static float Damage( Asteroid const& model )noexcept;
		static float Health( Asteroid const& model )noexcept;
		static AsteroidDeathReason Reason( Asteroid const& model )noexcept;
		static int ScoreValue( Asteroid const& model )noexcept;
	};
}