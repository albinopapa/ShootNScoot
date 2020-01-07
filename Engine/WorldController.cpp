#include "WorldController.h"
#include "Utilities.h"
#include "World.h"
#include "Game.h"

#include "AmmoController.h"
#include "AsteroidController.h"
#include "BossController.h"
#include "EnemyController.h"
#include "GameController.h"
#include "HeroController.h"
#include "ShieldController.h"
#include "StarController.h"

namespace sns
{
	void WorldController::Update( World& model, Keyboard& kbd, Game& game, float dt )
	{
		for( auto& star : model.stars ) StarController::Update( star );

		HeroController::Update( model.hero, model, kbd, dt );

		for( auto& ammo : model.hero_bullets ) AmmoController::Update( ammo, dt );

		for( auto& ammo : model.enemy_bullets ) AmmoController::Update( ammo, dt );

		switch( model.state )
		{
			case WorldState::Arena:
			{
				for( auto& enemy : model.enemies ) EnemyController::Update( enemy, dt );
				for( auto& astro : model.asteroids ) AsteroidController::Update( astro, dt );

				for( auto& enemy : model.enemies ) DoEnemyCollision( model, enemy, game );
				for( auto& bullet : model.enemy_bullets ) DoEnemyAmmoCollision( model, bullet );
				for( auto& astro : model.asteroids ) DoAsteroidCollision( model, astro, game );

				RemoveDeadBullets( model );
				RemoveDeadEnemies( model );
				RemoveDeadAsteroids( model );

				if( model.astro_spawner.GetState() == AsteroidSpawner::State::Complete &&
					model.enemy_spawner.GetState() == EnemySpawner::State::Complete )
				{
					model.state = WorldState::Boss;
					switch( model.level )
					{
						case 1:
							model.boss = { Boss1{} };
							break;
						case 2:
							model.boss = { Boss2{} };
							break;
					}
					++model.level;
				}

				break;
			}
			case WorldState::Boss:
			{
				BossController::Update( model.boss, model, dt );

				DoBossCollision( model, game );
				for( auto& bullet : model.enemy_bullets ) DoBossAmmoCollision( model, bullet );

				if( BossController::Health( model.boss ) <= 0.f )
				{
					model.state = WorldState::LevelComplete;
					model.astro_spawner.Reset();
					model.enemy_spawner.Reset();
				}
				break;
			}
		}
	}

	void WorldController::RemoveDeadBullets( World& model ) noexcept
	{
		auto ammo_is_dead = 
			[ & ]( Ammo const& bullet ) { return !AmmoController::IsAlive( bullet ); };

		erase_if( model.hero_bullets, ammo_is_dead );
		erase_if( model.enemy_bullets, ammo_is_dead );
	}

	void WorldController::RemoveDeadEnemies( World& model ) noexcept
	{
		auto enemy_is_dead =
			[ & ]( Enemy const& enemy_ ) { return !EnemyController::IsAlive( enemy_ ); };

		erase_if( model.enemies, enemy_is_dead );
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
			model.SpawnAsteroid( Asteroid{ spawn_pos, direction, SmallAsteroid{} } );
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
		const auto enemy_aabb = EnemyController::AABB( enemy );

		// Enemy vs Hero
		auto& shield = HeroController::GetShield( model.hero );
		if( ShieldController::Health( shield ) > 0.f )
		{
			if( enemy_aabb.Overlaps( ShieldController::AABB( shield, model.hero.position ) ) )
			{
				EnemyController::TakeDamage( enemy, Hero::damage );
				ShieldController::TakeDamage( shield, EnemyController::Damage( enemy ) );
				if( EnemyController::Health( enemy ) <= 0.f )
				{
					GameController::IncrementScore( game, Enemy::score_value );
					return;
				}
			}
		}
		else
		{
			if( enemy_aabb.Overlaps( HeroController::AABB( model.hero ) ) )
			{
				EnemyController::TakeDamage( enemy, Hero::damage );
				HeroController::TakeDamage( model.hero, EnemyController::Damage( enemy ) );
				if( EnemyController::Health( enemy ) <= 0.f )
				{
					GameController::IncrementScore( game, Enemy::score_value );
					return;
				}
			}
		}

		// Enemy vs HeroAmmo
		for( auto& bullet : model.hero_bullets )
		{
			if( AmmoController::IsAlive( bullet ) )
			{
				if( enemy_aabb.Overlaps( AmmoController::AABB( bullet ) ) )
				{
					EnemyController::TakeDamage( enemy, AmmoController::Damage( bullet ) );
					AmmoController::TakeDamage( bullet, EnemyController::Damage( enemy ) );
					if( EnemyController::Health( enemy ) <= 0.f )
					{
						GameController::IncrementScore( game, Enemy::score_value );
						return;
					}
				}
			}
		}


		// Enemy vs Asteroid
		for( auto& astro : model.asteroids )
		{
			if( AsteroidController::Health( astro ) <= 0.f )continue;

			if( enemy_aabb.Overlaps( AsteroidController::AABB( astro ) ) )
			{
				EnemyController::TakeDamage( enemy, AsteroidController::Damage( astro ) );
				AsteroidController::TakeDamage( astro, EnemyController::Damage( enemy ) );
				if( AsteroidController::Health( astro ) <= 0.f )
				{
					AsteroidController::Reason( astro, AsteroidDeathReason::AffectedByEnemy );
				}
				if( EnemyController::Health( enemy ) <= 0.f )
				{
					return;
				}
			}
		}
	}

	void WorldController::DoEnemyAmmoCollision( World& model, Ammo& ammo ) noexcept
	{
		if( !AmmoController::IsAlive( ammo ) )return;
		const auto ammo_aabb = AmmoController::AABB( ammo );

		// EnemyAmmo vs Hero
		auto& shield = model.hero.shield;
		if( ShieldController::Health( shield ) > 0.f )
		{
			if( ammo_aabb.Overlaps( ShieldController::AABB( shield, model.hero.position ) ) )
			{
				AmmoController::TakeDamage( ammo, Hero::damage );
				ShieldController::TakeDamage( shield, AmmoController::Damage( ammo ) );
			}
		}
		else
		{
			if( ammo_aabb.Overlaps( HeroController::AABB( model.hero ) ) )
			{
				AmmoController::TakeDamage( ammo, Hero::damage );
				HeroController::TakeDamage( model.hero, AmmoController::Damage( ammo ) );
			}
		}

		if( !AmmoController::IsAlive( ammo ) )return;

		// EnemyAmmo vs Asteroid
		for( auto& astro : model.asteroids )
		{
			if( ammo_aabb.Overlaps( AsteroidController::AABB( astro ) ) )
			{
				AmmoController::TakeDamage( ammo, AsteroidController::Damage( astro ) );
				AsteroidController::TakeDamage( astro, AmmoController::Damage( ammo ) );
				if( AsteroidController::Health( astro ) <= 0.f )
					AsteroidController::Reason( astro, AsteroidDeathReason::AffectedByEnemy );
			}
		}
	}

	void WorldController::DoAsteroidCollision( World& model, Asteroid& asteroid, Game& game ) noexcept
	{
		const auto asteroid_aabb = AsteroidController::AABB( asteroid );

		// Asteroid vs Hero
		auto& shield = model.hero.shield;
		if( ShieldController::Health( shield ) > 0.f )
		{
			if( asteroid_aabb.Overlaps( ShieldController::AABB( shield, model.hero.position ) ) )
			{
				ShieldController::TakeDamage( shield, AsteroidController::Damage( asteroid ) );
				AsteroidController::TakeDamage( asteroid, Hero::damage );
				if( AsteroidController::Health( asteroid ) <= 0.f )
				{
					GameController::IncrementScore( game, AsteroidController::ScoreValue( asteroid ) );
					AsteroidController::Reason( asteroid, AsteroidDeathReason::AffectedByPlayer );
				}
			}
		}
		else
		{
			if( asteroid_aabb.Overlaps( HeroController::AABB( model.hero ) ) )
			{
				HeroController::TakeDamage( model.hero, AsteroidController::Damage(asteroid) );
				AsteroidController::TakeDamage( asteroid, Hero::damage );
				if( AsteroidController::Health( asteroid ) <= 0.f )
				{
					GameController::IncrementScore( game, AsteroidController::ScoreValue( asteroid ) );
					AsteroidController::Reason( asteroid, AsteroidDeathReason::AffectedByPlayer );
				}
			}
		}

		if( AsteroidController::Health( asteroid ) <= 0.f )return;

		// Asteroid vs HeroAmmo
		for( auto& bullet : model.hero_bullets )
		{
			if( AmmoController::IsAlive( bullet ) &&
				AmmoController::AABB( bullet ).Overlaps( asteroid_aabb ) )
			{
				AsteroidController::TakeDamage( asteroid, AmmoController::Damage( bullet ) );
				AmmoController::TakeDamage( bullet, AsteroidController::Damage( asteroid ) );
				if( AsteroidController::Health( asteroid ) <= 0.f )
				{
					GameController::IncrementScore( game, AsteroidController::ScoreValue( asteroid ) );
					AsteroidController::Reason( asteroid, AsteroidDeathReason::AffectedByPlayer );
				}
			}
		}

		// Asteroid vs Asteroid
		for( auto& astro : model.asteroids )
		{
			if( std::addressof( astro ) != std::addressof( asteroid ) )
			{
				if( AsteroidController::Health(astro) <= 0.f )continue;

				if( asteroid_aabb.Overlaps( AsteroidController::AABB(astro) ) )
				{
					AsteroidController::TakeDamage( astro, AsteroidController::Damage( asteroid ) );
					AsteroidController::TakeDamage( asteroid, AsteroidController::Damage( astro ) );
					if( AsteroidController::Health( astro ) <= 0.f )
						AsteroidController::Reason( astro, AsteroidDeathReason::AffectedByAsteroid );
					if( AsteroidController::Health( asteroid ) <= 0.f )
						AsteroidController::Reason( asteroid, AsteroidDeathReason::AffectedByAsteroid );
				}
			}
		}
	}

	void WorldController::DoBossCollision( World& model, Game& game ) noexcept
	{
		const auto boss_aabb = BossController::AABB( model.boss );
		
		if( boss_aabb.Overlaps( HeroController::AABB( model.hero ) ) )
		{
			BossController::TakeDamage( model.boss, HeroController::Damage( model.hero ) );
			HeroController::TakeDamage( model.hero, BossController::Damage( model.boss ) );
		}

		for( auto& bullet : model.hero_bullets )
		{
			if( !AmmoController::IsAlive( bullet ) )continue;

			if( boss_aabb.Overlaps( AmmoController::AABB( bullet ) ) )
			{
				BossController::TakeDamage( model.boss, AmmoController::Damage( bullet ) );
				AmmoController::TakeDamage( bullet, BossController::Damage( model.boss ) );
			}
		}

		if( BossController::Health( model.boss ) <= 0.f )
		{
			GameController::IncrementScore( game, 1000 );
			model.state = WorldState::Arena;
		}
	}

	void WorldController::DoBossAmmoCollision( World& model, Ammo& ammo ) noexcept
	{
		if( AmmoController::AABB( ammo ).Overlaps( HeroController::AABB( model.hero ) ) )
		{
			HeroController::TakeDamage( model.hero, AmmoController::Damage( ammo ) );
			AmmoController::TakeDamage( ammo, HeroController::Damage( model.hero) );
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
		model.astro_spawner.Reset();
		model.enemy_spawner.Reset();
		model.boss.Reset();
		model.level = 1;
	}

	bool WorldController::IsGameOver( World & model ) noexcept
	{
		return HeroController::Health( model.hero ) <= 0.f || model.level > 2;
	}

}
