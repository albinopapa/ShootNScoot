#pragma once

#include "Shield.h"
#include "Weapon.h"

namespace sns
{
	struct Boss1
	{
	public:
		Boss1()noexcept;
		void Update( float dt, struct World& world );
		void TakeDamage( float amount )noexcept;
		void Draw( class Surface const& sprite, class Graphics& gfx )const noexcept;
		void Reset()noexcept;
	public:
		enum class State { Idle, Attack, Regen };

	public:
		static constexpr auto aabb = RectF{ -16.f, -16.f, 16.f, 16.f };
		static constexpr auto damage = 50.f;
		static constexpr auto regen_delay = 3.f;
		static constexpr auto max_missiles = 10;
		static constexpr auto max_health = 200.f;
		static constexpr auto speed = 160.f;

		Shield shield;
		Weapon weapon;
		Vec2 position = { screenRect.Center().x, -32.f };
		Vec2 direction = { 0.f, 1.f };
		State state = State::Idle;
		float regen_timer = regen_delay;
		float health = max_health;
		int missile_count = 0;
	};

}
