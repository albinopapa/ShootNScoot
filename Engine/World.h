#pragma once

#include "Asteroids.h"
#include "Bullet.h"
#include "Bosses.h"
#include "Enemies.h"
#include "Grid.h"
#include "Hero.h"
#include "Levels.h"
#include "Star.h"
#include "Starfield.h"

namespace sns
{
	class World
	{
	public:
		using Controller = struct WorldController;
		enum class State
		{
			Arena, Boss, LevelComplete, HeroWon, HeroLost
		};
	public:
		void Update( float dt );

	private:
		friend struct WorldController;
		std::vector<Star> stars = Starfield::generate( screenRect, { 1.f, 2.f }, 250 );
		std::vector<Asteroid> asteroids;
		std::vector<Enemy> enemies;
		std::vector<Ammo> enemy_bullets;
		std::vector<Ammo> hero_bullets;

		Hero hero;
		Boss boss = Boss{ Boss1{} };
		Level level = Level{ Level1{} };
		Grid grid;
		State state = State::Arena;
	};

}