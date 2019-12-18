#pragma once

#include "Graphics.h"
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
		void Update( float dt )noexcept;
		void TakeDamage( float amount )noexcept;
		void Draw( Graphics& gfx )const noexcept;
		RectF AABB()const noexcept;
		float Damage()const noexcept;
		int ScoreValue()const noexcept;

		enum class DeathReason { None, LeftScreen, AffectedByPlayer, AffectedByEnemy, AffectedByAsteroid };
	public:
		static constexpr float speed = 200.f;
		static constexpr Color color = Color{ 200, 100, 50 };
		std::variant<BigAsteroid, SmallAsteroid> variant;
		Vec2 position, direction;
		float health = 100.f;
		DeathReason reason = DeathReason::None;
	};
}
