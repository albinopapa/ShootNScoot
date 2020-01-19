#pragma once

#include "Ammo.h"
#include "Asteroids.h"
#include "Bosses.h"
#include "Enemies.h"
#include "Grid.h"
#include "Hero.h"
#include "Levels.h"
#include "Star.h"
#include "Starfield.h"
#include "Settings.h"

namespace sns
{
	class World
	{
	public:
		enum class State
		{
			Arena, Boss, LevelComplete, HeroWon, HeroLost
		};

	private:
		friend class WorldController;
		friend class WorldView;

		std::vector<Star> stars = Starfield::generate( screen_rect, { 1.f, 2.f }, 250 );
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