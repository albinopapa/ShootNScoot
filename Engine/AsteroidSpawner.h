#pragma once

#include <random>

using float_distribution = std::uniform_real_distribution<float>;
namespace sns
{
	class Asteroid;
	class AsteroidSpawner
	{
	public:
		static Asteroid Spawn();

	private:
		static std::mt19937 rng;
		inline static float_distribution xDist	= float_distribution( -600.f, 600.f );
		inline static float_distribution vxDist	= float_distribution( 0.f, 1.f );
	};
}
