#pragma once

#include "Keyboard.h"

class Game;

namespace sns
{
	class Ammo;
	class Asteroid;
	class Enemy;
	class Hero;
	class Boss;
	class World;

	class WorldController
	{
	public:
		static void Update( World& model, Keyboard& kbd, Game& game_controller, float dt );
		static void Reset( World& model )noexcept;
		static void SpawnAsteroid( World& model, Asteroid const& asteroid );
		static void SpawnEnemy( World& model, Enemy enemy );
		static void SpawnAmmo( World& model, Ammo const& ammo );
		static bool HeroLost( World const& model )noexcept;
		static bool HeroWon( World const& model )noexcept;
		static int CurrentLevelIndex( World const& model )noexcept;
	private:
		static void DoCollisions( World& model, Game& game )noexcept;

		static void RemoveDeadBullets( World& model )noexcept;
		static void RemoveDeadEnemies( World& model )noexcept;
		static void RemoveDeadAsteroids( World& model )noexcept;

		template<typename T, typename U>
		static void DoCollision( T& lhs, U& rhs, Game& game )noexcept {}
		static void DoCollision( Asteroid& lhs, Asteroid& rhs, Game& game )noexcept;
		static void DoCollision( Asteroid& lhs, Ammo& rhs, Game& game )noexcept;
		static void DoCollision( Asteroid& lhs, Enemy& rhs, Game& game )noexcept;
		static void DoCollision( Asteroid& lhs, Hero& rhs, Game& game )noexcept;
		static void DoCollision( Ammo& lhs, Asteroid& rhs, Game& game )noexcept;
		static void DoCollision( Ammo& lhs, Boss& rhs, Game& game )noexcept;
		static void DoCollision( Ammo& lhs, Enemy& rhs, Game& game )noexcept;
		static void DoCollision( Ammo& lhs, Hero& rhs, Game& game )noexcept;
		static void DoCollision( Boss& lhs, Ammo& rhs, Game& game )noexcept;
		static void DoCollision( Boss& lhs, Hero& rhs, Game& game )noexcept;
		static void DoCollision( Enemy& lhs, Asteroid& rhs, Game& game )noexcept;
		static void DoCollision( Enemy& lhs, Ammo& rhs, Game& game )noexcept;
		static void DoCollision( Enemy& lhs, Hero& rhs, Game& game )noexcept;
		static void DoCollision( Hero& lhs, Asteroid& rhs, Game& game )noexcept;
		static void DoCollision( Hero& lhs, Ammo& rhs, Game& game )noexcept;
		static void DoCollision( Hero& lhs, Boss& rhs, Game& game )noexcept;
		static void DoCollision( Hero& lhs, Enemy& rhs, Game& game )noexcept;
	};
}
