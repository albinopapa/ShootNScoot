#pragma once

#include "Enumerations.h"
#include "Vec2.h"
#include <variant>

namespace sns
{
	struct BigAsteroid
	{
		static constexpr float radius = 24.f;
		static constexpr float damage = 6.f;
		static constexpr int score_value = 50;
	};

	struct SmallAsteroid
	{
		static constexpr float radius = 12.f;
		static constexpr float damage = 3.f;
		static constexpr int score_value = 25;
	};

	struct Asteroid
	{
	public:
		using AsteroidType = std::variant<BigAsteroid, SmallAsteroid>;

	public:
		Asteroid( Vec2 const& position_, Vec2 const& direction_, AsteroidType type )noexcept;
		void Update( float dt )noexcept;

	public:
		friend class AsteroidController;
		friend class AsteroidView;

		AsteroidType variant;
		Vec2 position, direction;
		float health = 100.f;
		AsteroidDeathReason reason = AsteroidDeathReason::None;
		static constexpr float speed = 200.f;
	};
}
