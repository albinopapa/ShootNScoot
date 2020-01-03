#include "EnemySpawner.h"
#include "Enemies.h"
#include "World.h"
#include "WorldView.h"
#include "WorldController.h"

void sns::EnemySpawner::Update( World& world, float dt )
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
						world.SpawnEnemy( { Enemy1{}, Enemy1::waypoints[ 0 ], {0.f, 0.f} } );
						break;
					}
					case 1:
					{
						world.SpawnEnemy( { Enemy2{}, Enemy2::waypoints[ 0 ], {0.f, 0.f} } );
						break;
					}
					case 2:
					{
						world.SpawnEnemy( { Enemy3{}, Enemy3::waypoints[ 0 ], {0.f, 0.f} } );
						break;
					}
					case 3:
					{
						world.SpawnEnemy( { Enemy4{}, Enemy4::waypoints[ 0 ], {0.f, 0.f} } );
						break;
					}
					case 4:
					{
						world.SpawnEnemy( { Enemy5{}, Enemy5::waypoints[ 0 ], {0.f, 0.f} } );
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

void sns::EnemySpawner::Reset() noexcept
{
	enemy_spawn_group			= 0;
	enemy_spawn_group_count		= 0;
	enemy_spawn_group_timer		= enemy_spawn_group_delay;
	enemy_spawn_timer			= 0.f;

	state						= State::Waiting;
}
