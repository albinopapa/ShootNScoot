#include "WorldController.h"
#include "Utilities.h"
#include "World.h"
#include "Game.h"

namespace sns
{
	void WorldController::Update( World& model, Keyboard& kbd, Game& game, float dt )
	{
		for( auto& star : model.stars ) star_controller.Update( star );

		hero_controller.Update( model.hero, model, kbd, dt );

		for( auto& ammo : model.hero_bullets ) ammo_controller.Update( ammo, dt );

		for( auto& ammo : model.enemy_bullets ) ammo_controller.Update( ammo, dt );

		switch( model.state )
		{
			case WorldState::Arena:
			{
				astro_spawner.Update( model, dt );
				enemy_spawner.Update( model, dt );

				for( auto& enemy : model.enemies ) enemy_controller.Update( enemy, dt );
				for( auto& astro : model.asteroids ) asteroid_controller.Update( astro, dt );

				for( auto& enemy : model.enemies ) DoEnemyCollision( model, enemy, game );
				for( auto& bullet : model.enemy_bullets ) DoEnemyAmmoCollision( model, bullet );
				for( auto& astro : model.asteroids ) DoAsteroidCollision( model, astro, game );

				RemoveDeadBullets( model );
				RemoveDeadEnemies( model );
				RemoveDeadAsteroids( model );

				if( astro_spawner.state == AsteroidSpawner::State::Complete && model.asteroids.empty() &&
					enemy_spawner.state == EnemySpawner::State::Complete && model.enemies.empty() )
				{
					model.state = WorldState::Boss;
				}

				break;
			}
			case WorldState::Boss:
			{
				boss_controller.Update( model.boss, model, dt );

				DoBossCollision( model, game );
				for( auto& bullet : model.enemy_bullets ) DoBossAmmoCollision( model, bullet );

				if( model.boss.health <= 0.f )
				{
					model.state = WorldState::LevelComplete;
					astro_spawner.Reset();
					enemy_spawner.Reset();
				}
				break;
			}
		}
	}

	void WorldController::RemoveDeadBullets( World& model ) noexcept
	{
		erase_if( model.hero_bullets, [ & ]( Ammo const& bullet ) { return !bullet.isAlive; } );
		erase_if( model.enemy_bullets, [ & ]( Ammo const& bullet ) { return !bullet.isAlive; } );
	}

	void WorldController::RemoveDeadEnemies( World& model ) noexcept
	{
		erase_if( model.enemies, [ & ]( Enemy const& enemy_ ) { return enemy_.health <= 0.f; } );
	}

	void WorldController::RemoveDeadAsteroids( World& model ) noexcept
	{
		std::vector<Vec2> positions;
		positions.reserve( model.asteroids.size() );

		erase_if( model.asteroids, [ & ]( Asteroid const& astro ) 
		{
			if( astro.health > 0.f ) return false;
			
			if( std::holds_alternative<BigAsteroid>( astro.variant ) &&
				astro.reason != AsteroidDeathReason::LeftScreen )
			{
				positions.push_back( astro.position );
			}

			return true;
		} );

		constexpr auto nw = Vec2{ -.707f, -.707f };
		constexpr auto ne = Vec2{  .707f, -.707f };
		constexpr auto sw = Vec2{ -.707f,  .707f };
		constexpr auto se = Vec2{  .707f,  .707f };

		auto spawn = [ & ]( const auto& position, const auto& direction ) {
			const auto spawn_pos = position + ( direction * BigAsteroid::radius );
			model.SpawnAsteroid( Asteroid{ SmallAsteroid{}, spawn_pos, direction } );
		};

		for( auto const& position : positions )
		{
			spawn( position, nw );
			spawn( position, ne );
			spawn( position, sw );
			spawn( position, se );
		}
	}

	void WorldController::DoEnemyCollision( World& model, Enemy& enemy, Game& game ) noexcept
	{
		const auto enemy_aabb = enemy_controller.AABB( enemy );

		// Enemy vs Hero
		auto& shield = hero_controller.GetShield( model.hero );
		auto shield_controller = ShieldController{};
		if( shield_controller.Health( shield ) > 0.f )
		{
			if( enemy_aabb.Overlaps( shield_controller.AABB( shield, model.hero.position ) ) )
			{
				enemy_controller.TakeDamage( enemy, Hero::damage );
				shield_controller.TakeDamage( shield, enemy_controller.Damage( enemy ) );
				if( enemy_controller.Health( enemy ) <= 0.f )
				{
					game.IncrementScore( Enemy::score_value );
					return;
				}
			}
		}
		else
		{
			if( enemy_aabb.Overlaps( hero_controller.AABB( model.hero ) ) )
			{
				enemy_controller.TakeDamage( enemy, Hero::damage );
				hero_controller.TakeDamage( model.hero, enemy_controller.Damage( enemy ) );
				if( enemy_controller.Health( enemy ) <= 0.f )
				{
					game.IncrementScore( Enemy::score_value );
					return;
				}
			}
		}

		// Enemy vs HeroAmmo
		for( auto& bullet : model.hero_bullets )
		{
			if( ammo_controller.IsAlive( bullet ) )
			{
				if( enemy_aabb.Overlaps( ammo_controller.AABB( bullet ) ) )
				{
					enemy_controller.TakeDamage( enemy, ammo_controller.Damage( bullet ) );
					ammo_controller.TakeDamage( bullet, enemy_controller.Damage( enemy ) );
					if( enemy_controller.Health( enemy ) <= 0.f )
					{
						game.IncrementScore( Enemy::score_value );
						return;
					}
				}
			}
		}


		// Enemy vs Asteroid
		for( auto& astro : model.asteroids )
		{
			if( asteroid_controller.Health( astro ) <= 0.f )continue;

			if( enemy_aabb.Overlaps( asteroid_controller.AABB( astro ) ) )
			{
				enemy_controller.TakeDamage( enemy, asteroid_controller.Damage( astro ) );
				asteroid_controller.TakeDamage( astro, enemy_controller.Damage( enemy ) );
				if( asteroid_controller.Health( astro ) <= 0.f )
				{
					asteroid_controller.Reason( astro, AsteroidDeathReason::AffectedByEnemy );
				}
				if( enemy_controller.Health( enemy ) <= 0.f )
				{
					return;
				}
			}
		}
	}

	void WorldController::DoEnemyAmmoCollision( World& model, Ammo& ammo ) noexcept
	{
		if( !ammo_controller.IsAlive( ammo ) )return;
		const auto ammo_aabb = ammo_controller.AABB( ammo );

		// EnemyAmmo vs Hero
		auto& shield = model.hero.shield;
		auto shield_controller = ShieldController{};
		if( shield_controller.Health( shield ) > 0.f )
		{
			if( ammo_aabb.Overlaps( shield_controller.AABB( shield, model.hero.position ) ) )
			{
				ammo_controller.TakeDamage( ammo, Hero::damage );
				shield_controller.TakeDamage( shield, ammo_controller.Damage( ammo ) );
			}
		}
		else
		{
			if( ammo_aabb.Overlaps( hero_controller.AABB( model.hero ) ) )
			{
				ammo_controller.TakeDamage( ammo, Hero::damage );
				hero_controller.TakeDamage( model.hero, ammo_controller.Damage( ammo ) );
			}
		}

		if( !ammo_controller.IsAlive( ammo ) )return;

		// EnemyAmmo vs Asteroid
		for( auto& astro : model.asteroids )
		{
			if( ammo_aabb.Overlaps( asteroid_controller.AABB( astro ) ) )
			{
				ammo_controller.TakeDamage( ammo, asteroid_controller.Damage( astro ) );
				asteroid_controller.TakeDamage( astro, ammo_controller.Damage( ammo ) );
				if( asteroid_controller.Health( astro ) <= 0.f )
					asteroid_controller.Reason( astro, AsteroidDeathReason::AffectedByEnemy );
			}
		}
	}

	void WorldController::DoAsteroidCollision( World& model, Asteroid& asteroid, Game& game ) noexcept
	{
		const auto asteroid_aabb = asteroid_controller.AABB( asteroid );

		// Asteroid vs Hero
		auto& shield = model.hero.shield;
		auto shield_controller = ShieldController{};
		if( shield_controller.Health( shield ) > 0.f )
		{
			if( asteroid_aabb.Overlaps( shield_controller.AABB( shield, model.hero.position ) ) )
			{
				shield_controller.TakeDamage( shield, asteroid_controller.Damage( asteroid ) );
				asteroid_controller.TakeDamage( asteroid, Hero::damage );
				if( asteroid_controller.Health( asteroid ) <= 0.f )
				{
					game.IncrementScore( asteroid_controller.ScoreValue( asteroid ) );
					asteroid_controller.Reason( asteroid, AsteroidDeathReason::AffectedByPlayer );
				}
			}
		}
		else
		{
			if( asteroid_aabb.Overlaps( hero_controller.AABB( model.hero ) ) )
			{
				hero_controller.TakeDamage( model.hero, asteroid_controller.Damage(asteroid) );
				asteroid_controller.TakeDamage( asteroid, Hero::damage );
				if( asteroid_controller.Health( asteroid ) <= 0.f )
				{
					game.IncrementScore( asteroid_controller.ScoreValue( asteroid ) );
					asteroid_controller.Reason( asteroid, AsteroidDeathReason::AffectedByPlayer );
				}
			}
		}

		if( asteroid_controller.Health( asteroid ) <= 0.f )return;

		// Asteroid vs HeroAmmo
		for( auto& bullet : model.hero_bullets )
		{
			if( ammo_controller.IsAlive( bullet ) && 
				ammo_controller.AABB( bullet ).Overlaps( asteroid_aabb ) )
			{
				asteroid_controller.TakeDamage( asteroid, ammo_controller.Damage( bullet ) );
				ammo_controller.TakeDamage( bullet, asteroid_controller.Damage( asteroid ) );
				if( asteroid_controller.Health( asteroid ) <= 0.f )
				{
					game.IncrementScore( asteroid_controller.ScoreValue( asteroid ) );
					asteroid_controller.Reason( asteroid, AsteroidDeathReason::AffectedByPlayer );
				}
			}
		}

		// Asteroid vs Asteroid
		for( auto& astro : model.asteroids )
		{
			if( std::addressof( astro ) != std::addressof( asteroid ) )
			{
				if( asteroid_controller.Health(astro) <= 0.f )continue;

				if( asteroid_aabb.Overlaps( asteroid_controller.AABB(astro) ) )
				{
					asteroid_controller.TakeDamage( astro, asteroid_controller.Damage( asteroid ) );
					asteroid_controller.TakeDamage( asteroid, asteroid_controller.Damage( astro ) );
					if( asteroid_controller.Health( astro ) <= 0.f )
						asteroid_controller.Reason( astro, AsteroidDeathReason::AffectedByAsteroid );
					if( asteroid_controller.Health( asteroid ) <= 0.f )
						asteroid_controller.Reason( asteroid, AsteroidDeathReason::AffectedByAsteroid );
				}
			}
		}
	}

	void WorldController::DoBossCollision( World& model, Game& game ) noexcept
	{
		const auto boss_aabb = boss_controller.AABB( model.boss );
		
		if( boss_aabb.Overlaps( hero_controller.AABB( model.hero ) ) )
		{
			boss_controller.TakeDamage( model.boss, hero_controller.Damage( model.hero ) );
			hero_controller.TakeDamage( model.hero, boss_controller.Damage( model.boss ) );
		}

		for( auto& bullet : model.hero_bullets )
		{
			if( !ammo_controller.IsAlive( bullet ) )continue;

			if( boss_aabb.Overlaps( ammo_controller.AABB( bullet ) ) )
			{
				boss_controller.TakeDamage( model.boss, ammo_controller.Damage( bullet ) );
				ammo_controller.TakeDamage( bullet, boss_controller.Damage( model.boss ) );
			}
		}

		if( boss_controller.Health( model.boss ) <= 0.f )
		{
			game.IncrementScore( 1000 );
			model.state = WorldState::Arena;
		}
	}

	void WorldController::DoBossAmmoCollision( World& model, Ammo& ammo ) noexcept
	{
		if( ammo_controller.AABB( ammo ).Overlaps( hero_controller.AABB( model.hero ) ) )
		{
			hero_controller.TakeDamage( model.hero, ammo_controller.Damage( ammo ) );
			ammo_controller.TakeDamage( ammo, hero_controller.Damage( model.hero) );
		}
	}

	void WorldController::Reset( World& model )noexcept
	{
		model.enemy_bullets = std::vector<Ammo>{};
		model.enemies = std::vector<Enemy>{};
		model.hero_bullets = std::vector<Ammo>{};
		model.asteroids = std::vector<Asteroid>{};
		model.hero.Reset();
		model.state = WorldState::Arena;
		astro_spawner.Reset();
		enemy_spawner.Reset();
	}

}
