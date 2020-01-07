#include "EnemySpawner.h"
#include "Enemies.h"
#include "World.h"

namespace sns
{
	void EnemySpawner::Update( World& world, float dt )
	{
		switch( state )
		{
			case State::Waiting:
				enemy_spawn_group_timer -= dt;
				if( enemy_spawn_group_timer <= 0.f )
				{
					if( enemy_spawn_group < enemy_spawn_group_max )
						state = State::Spawning;
					else
						state = State::Complete;
				}
				break;
			case State::Spawning:
				enemy_spawn_timer -= dt;
				if( enemy_spawn_timer <= 0.f )
				{
					enemy_spawn_timer = enemy_spawn_rate;
					++enemy_spawn_group_count;

					switch( enemy_spawn_group )
					{
						case 0:
						{
							world.SpawnEnemy( { Enemy1{} } );
							break;
						}
						case 1:
						{
							world.SpawnEnemy( { Enemy2{} } );
							break;
						}
						case 2:
						{
							world.SpawnEnemy( { Enemy3{} } );
							break;
						}
						case 3:
						{
							world.SpawnEnemy( { Enemy4{} } );
							break;
						}
						case 4:
						{
							world.SpawnEnemy( { Enemy5{} } );
							break;
						}
						default:
							assert( false );
							break;
					}

					if( enemy_spawn_group_count > enemy_spawn_max )
					{
						enemy_spawn_group_timer = enemy_spawn_group_delay;
						++enemy_spawn_group;
						enemy_spawn_group_count = 0;
						state = State::Waiting;
					}
				}
				break;
			default:
				break;
		}
	}

	void EnemySpawner::Reset() noexcept
	{
		enemy_spawn_group			= 0;
		enemy_spawn_group_count		= 0;
		enemy_spawn_group_timer		= enemy_spawn_group_delay;
		enemy_spawn_timer			= 0.f;

		state						= State::Waiting;
	}

	EnemySpawner::State EnemySpawner::GetState() const noexcept
	{
		return State();
	}
}
