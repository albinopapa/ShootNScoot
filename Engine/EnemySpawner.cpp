#include "EnemySpawner.h"
#include "Enemies.h"
#include "World.h"
#include <string>
#include <stdexcept>

// TODO: Figure out enemy spawn points and their paths
namespace sns
{
	Enemy EnemySpawner::Spawn( int enemy_spawn_group ) noexcept
	{
		switch( enemy_spawn_group )
		{
			case 0:
				return { std::vector<Vec2>{}, Enemy1{} };
			case 1:
				return { std::vector<Vec2>{}, Enemy2{} };
			case 2:
				return { std::vector<Vec2>{}, Enemy3{} };
			case 3:
				return { std::vector<Vec2>{}, Enemy4{} };
			case 4:
				return { std::vector<Vec2>{}, Enemy5{} };
			default:
				assert( false );
				return { std::vector<Vec2>{}, Enemy1{} };
		}
	}
}
