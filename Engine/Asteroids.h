#pragma once

#include "EntityController.h"
#include "Rect.h"
#include "Vec2.h"
#include <variant>

namespace sns
{
	struct BigAsteroid
	{
		static constexpr float radius = 24.f;
		static constexpr RectF aabb = { -radius, -radius, radius, radius };
		static constexpr float damage = 6.f;
		static constexpr int score_value = 50;
	};

	struct SmallAsteroid
	{
		static constexpr float radius = 12.f;
		static constexpr auto aabb = RectF{ -radius, -radius, radius, radius };
		static constexpr float damage = 3.f;
		static constexpr int score_value = 25;
	};

	class Asteroid
	{
	public:
		using AsteroidType = std::variant<BigAsteroid, SmallAsteroid>;
		enum class DeathReason
		{
			None, LeftScreen, AffectedByPlayer, AffectedByEnemy, AffectedByAsteroid
		};

	public:
		Asteroid( Vec2 const& position_, Vec2 const& direction_, AsteroidType type )noexcept;

	private:
		friend class EntityController<Asteroid>;
		friend class AsteroidView;

		AsteroidType variant;
		Vec2 position;
		Vec2 direction;
		float health = 100.f;
		DeathReason reason = DeathReason::None;
		static constexpr float speed = 200.f;
	};
}
