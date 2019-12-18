#pragma once

#include "Asteroids.h"
#include "AsteroidSpawner.h"
#include "Bosses.h"
#include "Bullet.h"
#include "Enemies.h"
#include "EnemySpawner.h"
#include "Hero.h"
#include "Keyboard.h"
#include "StarField.h"

namespace sns
{
	struct World
	{
	public:
		void Update( Keyboard& kbd, float dt );
		void SpawnAsteroid( Asteroid const& astro );
		void SpawnBullet( Ammo const& ammo );
		void SpawnEnemy( Enemy const& enemy );
		void Draw( Graphics& gfx )const noexcept;

		void RemoveDeadBullets()noexcept;
		void RemoveDeadEnemies()noexcept;
		void RemoveDeadAsteroids()noexcept;

		void Reset()noexcept;

		// Enemy vs Hero, HeroAmmo, Asteroids
		void DoEnemyCollision( Enemy& enemy )noexcept;
		// EnemyAmmo vs Hero, Asteroid
		void DoEnemyAmmoCollision( Ammo& ammo )noexcept;
		// Asteroid vs Asteroid, HeroAmmo, Hero
		void DoAsteroidCollision( Asteroid& asteroid )noexcept;
		// Boss vs Hero, HeroAmmo
		void DoBossCollision()noexcept;
		// BossAmmo vs Hero
		void DoBossAmmoCollision( Ammo& ammo )noexcept;
	public:
		enum class State { Arena, Boss, LevelComplete };

		Surface enemy_ship								= "Images/Enemy1Ship.png";
		Surface hero_ship								= "Images/HeroShip.png";

		std::vector<Asteroid> asteroids;
		std::vector<Enemy> enemies;
		std::vector<Ammo> enemy_bullets;
		std::vector<Ammo> hero_bullets;

		StarField starfield;

		AsteroidSpawner astro_spawner;
		EnemySpawner enemy_spawner;

		Hero hero;
		Boss1 boss;
		State state = State::Arena;
		static constexpr float boss_delay = 60.f;
		float boss_delay_timer = boss_delay;
		int score = 0;
	};

}