#pragma once

#include "Enumerations.h"

class Shield
{
public:
	void Update( float delta_time )noexcept;
	void Reset()noexcept;

public:
	static constexpr float recharge_rate = 10.f;
	static constexpr float recharge_max = 100.f;
	static constexpr float recharge_delay = 2.f;
	static constexpr float health_min = -10.f;
	static constexpr float radius = 48.f;

	ShieldState state = ShieldState::Full;
	float recharge_delay_timer = recharge_delay;
	float health = 100.f;
};
