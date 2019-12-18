#pragma once

#include "Graphics.h"
#include <random>

namespace sns
{
	struct AsteroidSpawner
	{
		void Update( float dt, struct World& world );
		void Reset()noexcept;

		enum class State { Idle, Spawning, Complete };
		static constexpr int spawn_max = 20;
		static constexpr float spawn_delay = 4.f;

		std::mt19937 rng;
		std::uniform_real_distribution<float> xDist = std::uniform_real_distribution<float>( screenRect.Center().x - 600.f, screenRect.Center().x + 600.f );
		std::uniform_real_distribution<float> vxDist = std::uniform_real_distribution<float>( 0.f, 1.f );
		float spawn_timer = spawn_delay;
		int spawn_count = 0;
		State state = State::Idle;
	};
}