#pragma once

#include "ChiliMath.h"
#include "Graphics.h"
#include "Vec2.h"
#include <algorithm>

namespace sns
{
	struct Shield
	{
	public:
		void Update( float delta_time )noexcept;
		void TakeDamage( float amount )noexcept;
		void Draw( Vec2 const& center, Graphics& gfx )const noexcept;
		void Reset()noexcept;
		RectF AABB( Vec2 position )const noexcept;

	public:
		enum class State { Full, Recharging, Depleted };

	public:
		static constexpr float recharge_rate = 10.f;
		static constexpr float recharge_max = 100.f;
		static constexpr float recharge_delay = 2.f;
		static constexpr float health_min = -10.f;
		static constexpr float radius = 48.f;

		State state = State::Full;
		float recharge_delay_timer = recharge_delay;
		float health = 100.f;
	};
}
