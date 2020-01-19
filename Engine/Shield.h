#pragma once

#include "Surface.h"

namespace sns
{
	class Shield
	{
	public:
		enum class State { Full, Recharging, Depleted };

	private:
		static Surface MakeSprite();

	private:
		friend class ShieldController;
		friend class ShieldView;

		State state = State::Full;
		float recharge_delay_timer = recharge_delay;
		float health = 100.f;
		static const Surface sprite;
		static constexpr float recharge_rate = 10.f;
		static constexpr float recharge_max = 100.f;
		static constexpr float recharge_delay = 2.f;
		static constexpr float health_min = -10.f;
		static constexpr float radius = 48.f;
	};
}
