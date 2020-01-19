#include "AsteroidSpawner.h"
#include "Asteroids.h"
#include "RectController.h"
#include "Vec2Controller.h"
#include "World.h"


namespace sns
{
	std::mt19937 AsteroidSpawner::rng;

	Asteroid AsteroidSpawner::Spawn()
	{
		const auto px = xDist( rng );
		const auto vx = px > 0.f ? -vxDist( rng ) : vxDist( rng );

		return Asteroid{ Vec2{ px, world_rect.top }, Vec2Controller::Normalize( Vec2{ vx, 1.f } ), BigAsteroid{} };
	}
}
