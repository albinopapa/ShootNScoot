#include "EnemySpawner.h"
#include "Enemies.h"
#include "World.h"
#include <string>
#include <stdexcept>

namespace sns
{
	Enemy EnemySpawner::Spawn( int enemy_spawn_group ) noexcept
	{
		switch( enemy_spawn_group )
		{
			case 0:
				return { Enemy1{} };
			case 1:
				return { Enemy2{} };
			case 2:
				return { Enemy3{} };
			case 3:
				return { Enemy4{} };
			case 4:
				return { Enemy5{} };
			default:
				assert( false );
				throw std::invalid_argument( 
					"enemy_spawn_group = " + 
					std::to_string( enemy_spawn_group ) + 
					": is more than enemy_max_groups\n" );
		}
	}
}
