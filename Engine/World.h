#pragma once

#include "Asteroids.h"
#include "Bosses.h"
#include "Bullet.h"
#include "Enemies.h"
#include "Enumerations.h"
#include "Hero.h"
#include "Star.h"
#include "Starfield.h"
#include <vector>

namespace sns
{
	class World
	{
	public:
		void Update( float dt );

		void SpawnAsteroid( Asteroid const& asteroid );
		void SpawnEnemy( Enemy const& enemy );
		void SpawnAmmo( Ammo const& ammo );

	public:
		std::vector<Asteroid> asteroids;
		std::vector<Enemy> enemies;
		std::vector<Ammo> enemy_bullets;
		std::vector<Ammo> hero_bullets;

		std::vector<Star> stars = Starfield::generate( screenRect, { 1.f, 2.f }, 250 );

		Hero hero;
		Boss1 boss;
		WorldState state = WorldState::Arena;
	};

}