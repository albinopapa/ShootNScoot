#pragma once

#include "AmmoController.h"
#include "AsteroidController.h"
#include "AsteroidSpawner.h"
#include "Boss1Controller.h"
#include "EnemyController.h"
#include "EnemySpawner.h"
#include "HeroController.h"
#include "Keyboard.h"
#include "StarController.h"

class Game;

namespace sns
{
	class World;

	class WorldController
	{
	public:
		void Update( World& model, Keyboard& kbd, Game& game_controller, float dt );

		void RemoveDeadBullets( World& model )noexcept;
		void RemoveDeadEnemies( World& model );
		void RemoveDeadAsteroids( World& model )noexcept;

		// Enemy vs Hero, HeroAmmo, Asteroids
		void DoEnemyCollision( World& model, Enemy& enemy, Game& game )noexcept;
		// EnemyAmmo vs Hero, Asteroid
		void DoEnemyAmmoCollision( World& model, Ammo& ammo )noexcept;
		// Asteroid vs Asteroid, HeroAmmo, Hero
		void DoAsteroidCollision( World& model, Asteroid& asteroid, Game& game )noexcept;
		// Boss vs Hero, HeroAmmo
		void DoBossCollision( World& model, Game& game )noexcept;
		// BossAmmo vs Hero
		void DoBossAmmoCollision( World& model, Ammo& ammo )noexcept;

		void Reset( World& model )noexcept;

	private:
		AsteroidController asteroid_controller;
		AmmoController ammo_controller;
		EnemyController enemy_controller;
		StarController star_controller;
		
		AsteroidSpawner astro_spawner;
		EnemySpawner enemy_spawner;

		HeroController hero_controller;
		Boss1Controller boss_controller;
	};
}
