#include "World.h"

namespace sns
{
	void World::Update( float dt )
	{
		for( auto& star : stars ) star.Update();

		hero.Update( dt );
		for( auto& bullet : hero_bullets ) bullet.Update( dt );
		for( auto& bullet : enemy_bullets ) bullet.Update( dt );

		switch( state )
		{
			case State::Arena:
				level.Update( dt );

				for( auto& enemy : enemies ) enemy.Update( dt );
				for( auto& astro : asteroids ) astro.Update( dt );
				break;
			case State::Boss:
				boss.Update( dt );
				break;
		}
	}

}