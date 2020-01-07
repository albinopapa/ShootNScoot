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
			case WorldState::Arena:
				astro_spawner.Update( *this, dt );
				enemy_spawner.Update( *this, dt );

				for( auto& enemy : enemies ) enemy.Update( dt );
				for( auto& astro : asteroids ) astro.Update( dt );
				break;
			case WorldState::Boss:
				boss.Update( dt );
				break;
		}
	}

	void World::SpawnAsteroid( Asteroid const& asteroid )
	{
		asteroids.emplace_back( asteroid );
	}

	void World::SpawnEnemy( Enemy enemy_ )
	{
		enemies.emplace_back( std::move( enemy_ ) );
	}

	void World::SpawnAmmo( Ammo const & ammo )
	{
		if( ammo.owner == AmmoOwner::Enemy )
			enemy_bullets.emplace_back( ammo );
		else
			hero_bullets.emplace_back( ammo );
	}

}