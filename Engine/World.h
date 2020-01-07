#pragma once

#include "Asteroids.h"
#include "AsteroidSpawner.h"
#include "Bosses.h"
#include "Bullet.h"
#include "Enemies.h"
#include "EnemySpawner.h"
#include "Enumerations.h"
#include "Hero.h"
#include "Star.h"
#include "Starfield.h"
#include <vector>

namespace sns
{
	struct World
	{
	public:
		void Update( float dt );

		void SpawnAsteroid( Asteroid const& asteroid );
		void SpawnEnemy( Enemy enemy );
		void SpawnAmmo( Ammo const& ammo );

	public:
		std::vector<Asteroid> asteroids;
		std::vector<Enemy> enemies;
		std::vector<Ammo> enemy_bullets;
		std::vector<Ammo> hero_bullets;

		std::vector<Star> stars = Starfield::generate( screenRect, { 1.f, 2.f }, 250 );

		Hero hero;
		Boss boss = Boss{ Boss1{} };
		WorldState state = WorldState::Arena;

		AsteroidSpawner astro_spawner;
		EnemySpawner enemy_spawner;

		int level = 1;
		static constexpr auto max_demo_level = 2;
		static constexpr auto max_real_level = 10;
	};

}