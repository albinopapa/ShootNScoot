#pragma once

#include "Graphics.h"
#include <random>

using float_distribution = std::uniform_real_distribution<float>;
namespace sns
{
	class World;

	struct AsteroidSpawner
	{
		void Update( World& world, float dt );
		void Reset()noexcept;

		enum class State { Idle, Spawning, Complete };

		static constexpr int spawn_max		= 20;
		static constexpr float spawn_delay	= 4.f;

		std::mt19937 rng;
		float_distribution xDist			= float_distribution( screenRect.Center().x - 600.f, screenRect.Center().x + 600.f );
		float_distribution vxDist			= float_distribution( 0.f, 1.f );
		float spawn_timer					= spawn_delay;
		int spawn_count						= 0;
		State state							= State::Idle;
	};
}
