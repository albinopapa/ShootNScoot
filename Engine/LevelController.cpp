#include "LevelController.h"
#include "WorldController.h"
#include "Bosses.h"
#include "Levels.h"
#include "Enemies.h"
#include "World.h"

namespace sns
{
	void LevelController::Update( Level & model, World & world, float dt ) noexcept
	{
		UpdateAsteroidSpawner( model, world, dt );
		UpdateEnemySpawner( model, world, dt );
	}

	bool LevelController::AsteroidSpawnerComplete( Level const & model ) noexcept
	{
		return model.asteroid_state == Level::State::Complete;
	}

	bool LevelController::EnemySpawnerComplete( Level const & model ) noexcept
	{
		return model.enemy_state == Level::State::Complete;
	}

	bool LevelController::IsFinal( Level const & model ) noexcept
	{	
		return std::visit( [ & ]( auto const& level )
		{
			using type = std::decay_t<decltype( level )>;
			return std::is_same_v<type, Level10>;
		}, model.variant );
	}

	void LevelController::Reset( Level& model ) noexcept
	{
		model.variant = Level1{};

		model.asteroid_spawn_timer = 0.f;
		model.asteroid_spawn_count = 0;
		model.asteroid_state = Level::State::Idle;

		model.enemy_spawn_timer = 0.f;
		model.enemy_spawn_count = 0;
		model.enemy_spawn_group = 0;
		model.enemy_spawn_group_timer = 0.f;
		model.enemy_spawn_timer = 0.f;
		model.enemy_state = Level::State::Idle;
	}

	void LevelController::Advance( Level& model ) noexcept
	{
		std::visit( [ & ]( auto const& level )
		{
			using type = std::decay_t<decltype( level )>;
			if constexpr( std::is_same_v<type, Level1> )
			{
				model.variant = Level2{};
			}
			else if constexpr( std::is_same_v<type, Level2> )
			{
				model.variant = Level3{};
			}
			else if constexpr( std::is_same_v<type, Level3> )
			{
				model.variant = Level4{};
			}
			else if constexpr( std::is_same_v<type, Level4> )
			{
				model.variant = Level5{};
			}
			else if constexpr( std::is_same_v<type, Level5> )
			{
				model.variant = Level6{};
			}
			else if constexpr( std::is_same_v<type, Level6> )
			{
				model.variant = Level7{};
			}
			else if constexpr( std::is_same_v<type, Level7> )
			{
				model.variant = Level8{};
			}
			else if constexpr( std::is_same_v<type, Level8> )
			{
				model.variant = Level9{};
			}
			else if constexpr( std::is_same_v<type, Level9> )
			{
				model.variant = Level10{};
			}
		}, model.variant );
	}

	Boss LevelController::SpawnBoss( Level const& model ) noexcept
	{
		return std::visit( [ & ]( auto const& level )
		{
			using type = std::decay_t<decltype( level )>;
			return Boss{ type::BossType{} };
		}, model.variant );
	}

	int LevelController::CurrentLevelIndex( Level const & model ) noexcept
	{
		return int( model.variant.index() ) + 1;
	}

	void LevelController::UpdateAsteroidSpawner( Level & model, World & world, float dt ) noexcept
	{
		switch( model.asteroid_state )
		{
			case Level::State::Idle:
				std::visit( [ & ]( auto const& level )
				{
					model.asteroid_spawn_timer -= dt;
					if( model.asteroid_spawn_timer <= 0.f )
					{
						constexpr auto max_spawn =
							std::decay_t<decltype( level )>::asteroid_spawn_max;

						model.asteroid_state = ( model.asteroid_spawn_count < max_spawn ) ?
							Level::State::Spawning : Level::State::Complete;

					}
				}, model.variant );
				break;
			case Level::State::Spawning:
			{
				++model.asteroid_spawn_count;
				WorldController::SpawnAsteroid( world, AsteroidSpawner::Spawn() );
				model.asteroid_state = Level::State::Idle;
				break;
			}
			default:
				break;
		}
	}

	void LevelController::UpdateEnemySpawner( Level & model, World & world, float dt ) noexcept
	{
		std::visit( [ & ]( auto const& level )
		{
			using type = std::decay_t<decltype( level )>;

			switch( model.enemy_state )
			{
				case Level::State::Idle:
					model.enemy_spawn_group_timer -= dt;
					if( model.enemy_spawn_group_timer <= 0.f )
					{
						model.enemy_state = model.enemy_spawn_group < type::enemy_spawn_group_max ?
							Level::State::Spawning : Level::State::Complete;
					}
					break;
				case Level::State::Spawning:
					model.enemy_spawn_timer -= dt;
					if( model.enemy_spawn_timer <= 0.f )
					{
						model.enemy_spawn_timer = type::enemy_spawn_rate;

						++model.enemy_spawn_count;
						WorldController::SpawnEnemy( world, EnemySpawner::Spawn( model.enemy_spawn_group ) );

						if( model.enemy_spawn_count > type::enemy_spawn_max )
						{
							model.enemy_spawn_group_timer = type::enemy_spawn_group_delay;
							++model.enemy_spawn_group;
							model.enemy_spawn_count = 0;
							model.enemy_state = Level::State::Idle;
						}
					}
					break;
				default:
					break;
			}
		}, model.variant );
	}
}
