#include "World.h"
#include "Utilities.h"

namespace sns
{
	void World::Update( Keyboard & kbd, float dt )
	{
		starfield.Update();
		hero.Update( kbd, dt, *this );
		for( auto& bullet : hero_bullets ) bullet.Update( dt );
		for( auto& bullet : enemy_bullets ) bullet.Update( dt );

		switch( state )
		{
			case State::Arena:
				boss_delay_timer -= dt;

				astro_spawner.Update( dt, *this );
				enemy_spawner.Update( dt, *this );

				for( auto& enemy : enemies ) enemy.Update( dt );
				for( auto& astro : asteroids ) astro.Update( dt );
				for( auto& enemy : enemies ) DoEnemyCollision( enemy );
				for( auto& bullet : enemy_bullets ) DoEnemyAmmoCollision( bullet );
				for( auto& astro : asteroids ) DoAsteroidCollision( astro );

				RemoveDeadBullets();
				RemoveDeadEnemies();
				RemoveDeadAsteroids();

				if( astro_spawner.state == AsteroidSpawner::State::Complete &&
					enemy_spawner.state == EnemySpawner::State::Complete )
				{
					state = State::Boss;
				}

				break;
			case State::Boss:
				boss.Update( dt, *this );
				DoBossCollision();
				for( auto& bullet : enemy_bullets ) DoBossAmmoCollision( bullet );
				if( boss.health <= 0.f ) 
				{
					boss_delay_timer = boss_delay;
					astro_spawner.Reset();
					enemy_spawner.Reset();
					state = State::LevelComplete;
				}
				break;
		}

	}

	void World::SpawnAsteroid( Asteroid const & astro )
	{
		asteroids.push_back( astro );
	}

	void World::SpawnBullet( Ammo const& ammo ) {
		if( ammo.owner == Ammo::Owner::Hero )
			hero_bullets.push_back( ammo );
		else
			enemy_bullets.push_back( ammo );
	}

	void World::RemoveDeadBullets( ) noexcept
	{
		erase_if( hero_bullets, [ & ]( Ammo const& bullet ){ return !bullet.isAlive; } );
		erase_if( enemy_bullets, [ & ]( Ammo const& bullet ) {return !bullet.isAlive; } );
	}

	void World::RemoveDeadEnemies() noexcept
	{
		erase_if(enemies, [ & ]( Enemy const& enemy_ ) { return enemy_.health <= 0.f; } );
	}

	void World::RemoveDeadAsteroids() noexcept
	{
		std::vector<Vec2> positions;
		positions.reserve( 10 );

		erase_if( asteroids, [ & ]( Asteroid const& astro ) {
			if( astro.health <= 0.f )
			{
				if( std::holds_alternative<BigAsteroid>( astro.variant ) &&
					astro.reason != Asteroid::DeathReason::LeftScreen )
					positions.push_back( astro.position );

				return true;
			}

			return false;
		} );

		constexpr auto nw = Vec2{ -.707f, -.707f };
		constexpr auto ne = Vec2{ .707f, -.707f };
		constexpr auto sw = Vec2{ -.707f, .707f };
		constexpr auto se = Vec2{ .707f, .707f };

		auto spawn = [ & ]( const auto& position, const auto& direction ) {
			const auto spawn_pos = position + ( direction * BigAsteroid::radius );
			SpawnAsteroid( Asteroid{ SmallAsteroid{}, spawn_pos, direction } );
		};

		for( auto const& position : positions )
		{
			spawn( position, nw );
			spawn( position, ne );
			spawn( position, sw );
			spawn( position, se );
		}
	}

	void World::SpawnEnemy( Enemy const& enemy )
	{
		enemies.push_back( enemy );
	}

	void World::Reset()noexcept
	{
		enemy_bullets	= std::vector<Ammo>{};
		enemies			= std::vector<Enemy>{};
		hero_bullets	= std::vector<Ammo>{};
		asteroids		= std::vector<Asteroid>{};
		score			= 0;
		astro_spawner.Reset();
		hero.Reset();
		enemy_spawner.Reset();
		boss_delay_timer = boss_delay;
		state = State::Arena;
	}

	void World::DoEnemyCollision( Enemy & enemy ) noexcept
	{
		const auto enemy_aabb = enemy.AABB();

		// Enemy vs Hero
		if( hero.shield.health > 0.f )
		{
			if( enemy_aabb.Overlaps( hero.shield.AABB( hero.position ) ) )
			{
				enemy.TakeDamage( Hero::damage );
				hero.shield.TakeDamage( enemy.Damage() );
				if( enemy.health <= 0.f )
					score += Enemy::score_value;
			}
		}
		else
		{
			if( enemy_aabb.Overlaps( hero.AABB() ) )
			{
				enemy.TakeDamage( Hero::damage );
				hero.TakeDamage( enemy.Damage() );
				if( enemy.health <= 0.f )
					score += Enemy::score_value;
			}
		}

		if( enemy.health <= 0.f )return;

		// Enemy vs HeroAmmo
		for( auto& bullet : hero_bullets )
		{
			if( bullet.isAlive )
			{
				if( enemy_aabb.Overlaps( bullet.AABB() ) )
				{
					enemy.TakeDamage( bullet.Damage() );
					bullet.TakeDamage( enemy.Damage() );
					if( enemy.health <= 0.f )
						score += Enemy::score_value;
				}
			}
		}

		if( enemy.health <= 0.f )return;

		// Enemy vs Asteroid
		for( auto& astro : asteroids )
		{
			if( astro.health <= 0.f )continue;
			if( enemy.health <= 0.f )return;

			if( enemy_aabb.Overlaps( astro.AABB() ) )
			{
				enemy.TakeDamage( astro.Damage() );
				astro.TakeDamage( enemy.Damage() );
				if(astro.health <= 0.f)
					astro.reason = Asteroid::DeathReason::AffectedByEnemy;
			}
		}
	}
	void World::DoEnemyAmmoCollision( Ammo & ammo ) noexcept
	{
		if( !ammo.isAlive )return;
		const auto ammo_aabb = ammo.AABB();

		// EnemyAmmo vs Hero
		if( hero.shield.health > 0.f )
		{
			if( ammo_aabb.Overlaps( hero.shield.AABB( hero.position ) ) )
			{
				ammo.TakeDamage( Hero::damage );
				hero.shield.TakeDamage( ammo.Damage() );
			}
		}
		else
		{
			if( ammo_aabb.Overlaps( hero.AABB() ) )
			{
				ammo.TakeDamage( Hero::damage );
				hero.TakeDamage( ammo.Damage() );
			}
		}

		if( !ammo.isAlive )return;

		// EnemyAmmo vs Asteroid
		for( auto& astro : asteroids )
		{
			if( ammo_aabb.Overlaps( astro.AABB() + astro.position ) )
			{
				ammo.TakeDamage( astro.Damage() );
				astro.TakeDamage( ammo.Damage() );
				if(astro.health <= 0.f)
					astro.reason = Asteroid::DeathReason::AffectedByEnemy;
			}
		}
	}
	void World::DoAsteroidCollision( Asteroid & asteroid ) noexcept
	{
		const auto asteroid_aabb = asteroid.AABB();
		
		// Asteroid vs Hero
		if( hero.shield.health > 0.f )
		{
			if( asteroid_aabb.Overlaps( hero.shield.AABB( hero.position ) ) )
			{
				hero.shield.TakeDamage( asteroid.Damage() );
				asteroid.TakeDamage( Hero::damage );
				if( asteroid.health <= 0.f )
				{
					score += asteroid.ScoreValue();
					asteroid.reason = Asteroid::DeathReason::AffectedByPlayer;
				}
			}
		}
		else 
		{
			if( asteroid_aabb.Overlaps( hero.AABB() ) )
			{
				hero.TakeDamage( asteroid.Damage() );
				asteroid.TakeDamage( Hero::damage );
				if( asteroid.health <= 0.f )
				{
					score += asteroid.ScoreValue();
					asteroid.reason = Asteroid::DeathReason::AffectedByPlayer;
				}
			}
		}

		if( asteroid.health <= 0.f )return;

		// Asteroid vs HeroAmmo
		for( auto& bullet : hero_bullets )
		{
			if( bullet.isAlive && bullet.AABB().Overlaps( asteroid_aabb ) )
			{
				asteroid.TakeDamage( bullet.Damage() );
				bullet.TakeDamage( asteroid.Damage() );
				if( asteroid.health <= 0.f )
				{
					score += asteroid.ScoreValue();
					asteroid.reason = Asteroid::DeathReason::AffectedByPlayer;
				}
			}
		}

		// Asteroid vs Asteroid
		for( auto& astro : asteroids )
		{
			if( std::addressof( astro ) != std::addressof( asteroid ) )
			{
				if( astro.health <= 0.f )continue;

				if( asteroid_aabb.Overlaps( astro.AABB() ) )
				{
					astro.TakeDamage( asteroid.Damage() );
					asteroid.TakeDamage( astro.Damage() );
					if(astro.health <= 0.f)
						astro.reason = Asteroid::DeathReason::AffectedByAsteroid;
					if(asteroid.health <= 0.f)
						asteroid.reason = Asteroid::DeathReason::AffectedByAsteroid;
				}
			}
		}
	}

	void World::DoBossCollision() noexcept
	{
		const auto boss_aabb = Boss1::aabb + boss.position;
		if( boss_aabb.Overlaps( hero.AABB() ) )
		{
			boss.TakeDamage( hero.damage );
			hero.TakeDamage( boss.damage );
		}

		for( auto& bullet : hero_bullets )
		{
			if( !bullet.isAlive )continue;

			if( boss_aabb.Overlaps( bullet.AABB() ) )
			{
				boss.TakeDamage( bullet.Damage() );
				bullet.TakeDamage( boss.damage );
			}
		}

		if( boss.health <= 0.f )
		{
			score += 1000;
			state = State::Arena;
		}
	}

	void World::DoBossAmmoCollision( Ammo & ammo ) noexcept
	{
		if( ammo.AABB().Overlaps( hero.AABB() ) )
		{
			hero.TakeDamage( ammo.Damage() );
			ammo.TakeDamage( hero.damage );
		}
	}

	void World::Draw( Graphics & gfx ) const noexcept
	{
		starfield.Draw( gfx );
		hero.Draw( hero_ship, gfx );
		for( auto const& bullet : hero_bullets ) bullet.Draw( gfx );
		for( auto const& bullet : enemy_bullets ) bullet.Draw( gfx );

		switch( state )
		{
			case State::Arena:
				for( auto const& enemy : enemies ) enemy.Draw( enemy_ship, gfx );
				for( auto const& asteroid : asteroids ) asteroid.Draw( gfx );
				break;
			case State::Boss:
				boss.Draw( enemy_ship, gfx );
				break;
		}

	}
}