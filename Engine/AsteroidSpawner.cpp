#include "AsteroidSpawner.h"
#include "Asteroids.h"
#include "World.h"


namespace sns
{
	std::mt19937 AsteroidSpawner::rng = {};

	Asteroid AsteroidSpawner::Spawn()
	{
		constexpr auto cx = screenRect.Center().x;
		constexpr auto cy = screenRect.Center().y;

		const auto px = xDist( rng );
		const auto vx = px > cx ? -vxDist( rng ) : vxDist( rng );

		return Asteroid{ Vec2{ px, -50.f }, Vec2{ vx, 1.f }.Normalize(), BigAsteroid{} };
	}
}
