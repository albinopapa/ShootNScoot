#pragma once

#include "AsteroidSpawner.h"
#include "EnemySpawner.h"
#include "RectController.h"
#include "Settings.h"
#include <variant>

namespace sns
{
	struct Boss1;
	struct Boss2;
	struct Boss3;
	struct Boss4;
	struct Boss5;
	struct Boss6;
	struct Boss7;
	struct Boss8;
	struct Boss9;
	struct Boss10;

	struct Level1
	{
		using BossType = Boss1;
		static constexpr Vec2	hero_start_pos			= RectController::Center( world_rect );
		static constexpr int	asteroid_spawn_max		= 20;
		static constexpr float	asteroid_spawn_delay	= 6.f;

		static constexpr int	cycles					= 2;
		static constexpr float	enemy_spawn_group_delay = 4.f;
		static constexpr int	enemy_spawn_group_max	= 5;
		static constexpr float	enemy_spawn_rate		= .5f;
		static constexpr int	enemy_spawn_max			= 5;
	};

	struct Level2
	{
		using BossType = Boss2;
		static constexpr Vec2	hero_start_pos = RectController::Center( world_rect );
		static constexpr int	asteroid_spawn_max = 20;
		static constexpr float	asteroid_spawn_delay = 4.f;

		static constexpr int	cycles = 3;
		static constexpr float	enemy_spawn_group_delay = 4.f;
		static constexpr int	enemy_spawn_group_max = 5;
		static constexpr float	enemy_spawn_rate = .5f;
		static constexpr int	enemy_spawn_max = 5;
	};
	
	struct Level3 
	{
		using BossType = Boss3;
		static constexpr Vec2	hero_start_pos = RectController::Center( world_rect );
		static constexpr int	asteroid_spawn_max = 20;
		static constexpr float	asteroid_spawn_delay = 4.f;

		static constexpr int	cycles = 4;
		static constexpr float	enemy_spawn_group_delay = 3.f;
		static constexpr int	enemy_spawn_group_max = 5;
		static constexpr float	enemy_spawn_rate = .5f;
		static constexpr int	enemy_spawn_max = 5;
	};

	struct Level4 // Asteroid field level
	{
		using BossType = Boss4;
		static constexpr Vec2	hero_start_pos = RectController::Center( world_rect );
		static constexpr int	asteroid_spawn_max = 200;
		static constexpr float	asteroid_spawn_delay = 4.f;

		static constexpr int	cycles = 0;
		static constexpr float	enemy_spawn_group_delay = 3.f;
		static constexpr int	enemy_spawn_group_max = 5;
		static constexpr float	enemy_spawn_rate = .5f;
		static constexpr int	enemy_spawn_max = 5;
	};
	
	struct Level5 
	{
		using BossType = Boss5;
		static constexpr Vec2	hero_start_pos = RectController::Center( world_rect );
		static constexpr int	asteroid_spawn_max = 20;
		static constexpr float	asteroid_spawn_delay = 4.f;

		static constexpr int	cycles = 7;
		static constexpr float	enemy_spawn_group_delay = 2.f;
		static constexpr int	enemy_spawn_group_max = 5;
		static constexpr float	enemy_spawn_rate = .5f;
		static constexpr int	enemy_spawn_max = 5;
	};

	struct Level6 
	{
		using BossType = Boss6;
		static constexpr Vec2	hero_start_pos = RectController::Center( world_rect );
		static constexpr int	asteroid_spawn_max = 20;
		static constexpr float	asteroid_spawn_delay = 4.f;

		static constexpr int	cycles = 8;
		static constexpr float	enemy_spawn_group_delay = 2.f;
		static constexpr int	enemy_spawn_group_max = 5;
		static constexpr float	enemy_spawn_rate = .5f;
		static constexpr int	enemy_spawn_max = 5;
	};

	struct Level7 
	{
		using BossType = Boss7;
		static constexpr Vec2	hero_start_pos = RectController::Center( world_rect );
		static constexpr int	asteroid_spawn_max = 20;
		static constexpr float	asteroid_spawn_delay = 4.f;

		static constexpr int	cycles = 7;
		static constexpr float	enemy_spawn_group_delay = 1.f;
		static constexpr int	enemy_spawn_group_max = 5;
		static constexpr float	enemy_spawn_rate = .5f;
		static constexpr int	enemy_spawn_max = 5;
	};

	struct Level8 
	{
		using BossType = Boss8;
		static constexpr Vec2	hero_start_pos = RectController::Center( world_rect );
		static constexpr int	asteroid_spawn_max = 20;
		static constexpr float	asteroid_spawn_delay = 4.f;

		static constexpr int	cycles = 8;
		static constexpr float	enemy_spawn_group_delay = 1.f;
		static constexpr int	enemy_spawn_group_max = 5;
		static constexpr float	enemy_spawn_rate = .5f;
		static constexpr int	enemy_spawn_max = 5;
	};

	struct Level9 
	{
		using BossType = Boss9;
		static constexpr Vec2	hero_start_pos = RectController::Center( world_rect );
		static constexpr int	asteroid_spawn_max = 20;
		static constexpr float	asteroid_spawn_delay = 4.f;

		static constexpr int	cycles = 9;
		static constexpr float	enemy_spawn_group_delay = 1.f;
		static constexpr int	enemy_spawn_group_max = 5;
		static constexpr float	enemy_spawn_rate = .5f;
		static constexpr int	enemy_spawn_max = 5;
	};

	struct Level10 
	{
		using BossType = Boss10;
		static constexpr Vec2	hero_start_pos = RectController::Center( world_rect );
		static constexpr int	asteroid_spawn_max = 20;
		static constexpr float	asteroid_spawn_delay = 4.f;

		static constexpr int	cycles = 10;					// Number of waves
		static constexpr float	enemy_spawn_group_delay = 1.f;	// delay between groups
		static constexpr int	enemy_spawn_group_max = 5;		// Number of enemy types
		static constexpr float	enemy_spawn_rate = .5f;			// delay between enemies
		static constexpr int	enemy_spawn_max = 5;			// Number of enemies per wave
	};

	class Level
	{
	public:
		using LevelType = std::variant<
			Level1, 
			Level2, 
			Level3, 
			Level4, 
			Level5, 
			Level6, 
			Level7, 
			Level8, 
			Level9, 
			Level10
		>;

	public:
		enum class State { Idle, Spawning, Complete };

	public:
		Level( LevelType type )noexcept;

	private:
		friend class LevelController;

		LevelType		variant;

		float			asteroid_spawn_timer	= 0.f;
		int				asteroid_spawn_count	= 0;
		State			asteroid_state			= State::Idle;

		int				enemy_spawn_group		= 0;			// Enemy#
		float			enemy_spawn_group_timer	= 0.f;			// time to spawn a new group
		float			enemy_spawn_timer		= 0.f;			// time to spawn a new enemy
		int				enemy_spawn_count		= 0;			// enemies per group
		State			enemy_state				= State::Idle;
	};
}