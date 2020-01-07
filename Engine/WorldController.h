#pragma once

#include "Keyboard.h"

class Game;

namespace sns
{
	class Ammo;
	class Asteroid;
	class Enemy;
	class World;

	class WorldController
	{
	public:
		static void Update( World& model, Keyboard& kbd, Game& game_controller, float dt );
		static void Reset( World& model )noexcept;
		static bool IsGameOver( World& model )noexcept;

	private:
		static void RemoveDeadBullets( World& model )noexcept;
		static void RemoveDeadEnemies( World& model )noexcept;
		static void RemoveDeadAsteroids( World& model )noexcept;

		// Enemy vs Hero, HeroAmmo, Asteroids
		static void DoEnemyCollision( World& model, Enemy& enemy, Game& game )noexcept;
		// EnemyAmmo vs Hero, Asteroid
		static void DoEnemyAmmoCollision( World& model, Ammo& ammo )noexcept;
		// Asteroid vs Asteroid, HeroAmmo, Hero
		static void DoAsteroidCollision( World& model, Asteroid& asteroid, Game& game )noexcept;
		// Boss vs Hero, HeroAmmo
		static void DoBossCollision( World& model, Game& game )noexcept;
		// BossAmmo vs Hero
		static void DoBossAmmoCollision( World& model, Ammo& ammo )noexcept;
	};
}
