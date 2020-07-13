#pragma once

#include "Enumerations.h"
#include "Graphics.h"		// For screenRect
#include "Shield.h"
#include "Weapon.h"

namespace sns
{
	class Boss1
	{
	public:
		Boss1()noexcept;
		void Update( float dt );
		void Reset()noexcept;
	public:
		

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
		Boss1State state = Boss1State::Idle;
		float regen_timer = regen_delay;
		float health = max_health;
		int missile_count = 0;
	};

}
