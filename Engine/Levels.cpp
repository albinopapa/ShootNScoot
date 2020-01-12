#include "Levels.h"

sns::Level::Level( LevelType type ) noexcept
	:
	variant( type )
{
}

void sns::Level::Update( float dt )
{
	DoAsteroidSpawn( dt );
	DoEnemySpawnUpdate( dt );
}

void sns::Level::Reset() noexcept
{
	variant = Level1{};

	asteroid_spawn_timer = 0.f;
	asteroid_spawn_count = 0;
	asteroid_state = State::Idle;

	enemy_spawn_timer = 0.f;
	enemy_spawn_count = 0;
	enemy_spawn_group = 0;
	enemy_spawn_group_timer = 0.f;
	enemy_spawn_timer = 0.f;
	enemy_state = State::Idle;

}

void sns::Level::DoAsteroidSpawn( float dt )
{
	switch( asteroid_state )
	{
		case State::Idle:
			asteroid_spawn_timer -= dt;
			break;
		case State::Spawning:
		{
			++asteroid_spawn_count;
			break;
		}
		default:
			break;
	}
}

void sns::Level::DoEnemySpawnUpdate( float dt )
{
	switch( enemy_state )
	{
		case State::Idle:
			enemy_spawn_group_timer -= dt;
			break;
		case State::Spawning:
			enemy_spawn_timer -= dt;
			break;
		default:
			break;
	}
}
