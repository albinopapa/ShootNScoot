#include "WorldController.h"
#include "Utilities.h"
#include "World.h"
#include "Game.h"

#include "AmmoController.h"
#include "AsteroidController.h"
#include "BossController.h"
#include "CellController.h"
#include "EnemyController.h"
#include "GameController.h"
#include "GridController.h"
#include "HeroController.h"
#include "ShieldController.h"
#include "StarController.h"
#include "LevelController.h"

namespace sns
{
	void WorldController::Update( World& model, Keyboard& kbd, Game& game, float dt )
	{
		GridController::ClearCells( model.grid );

		for( auto& star : model.stars ) StarController::Update( star );

		EntityController<Hero>::Update( model.hero, model, kbd, dt );
		GridController::AddObject( model.grid, &model.hero );

		for( auto& ammo : model.hero_bullets )
		{
			EntityController<Ammo>::Update( ammo, dt );
			GridController::AddObject( model.grid, &ammo );
		}

		for( auto& ammo : model.enemy_bullets )
		{
			EntityController<Ammo>::Update( ammo, dt );
			GridController::AddObject( model.grid, &ammo );
		}

		DoCollisions( model, game );

		RemoveDeadBullets( model );
		RemoveDeadEnemies( model );
		RemoveDeadAsteroids( model );

		switch( model.state )
		{
			case World::State::Arena:
			{
				for( auto& enemy : model.enemies )
				{
					EntityController<Enemy>::Update( enemy, dt );
					GridController::AddObject( model.grid, &enemy );
				}

				for( auto& astro : model.asteroids )
				{
					EntityController<Asteroid>::Update( astro, dt );
					GridController::AddObject( model.grid, &astro );
				}

				if( LevelController::AsteroidSpawnerComplete( model.level ) &&
					LevelController::EnemySpawnerComplete( model.level ) )
				{
					model.state = World::State::Boss;
					model.boss = LevelController::SpawnBoss( model.level );
					GridController::AddObject( model.grid, &model.boss );
				}

				if( EntityController<Hero>::Health( model.hero ) <= 0.f )
					model.state = World::State::HeroLost;

				break;
			}
			case World::State::LevelComplete:
			{
				if( !LevelController::IsFinal( model.level ) )
				{
					LevelController::Advance( model.level );
					model.state = World::State::Arena;
				}
				else
				{
					model.state = World::State::HeroWon;
				}
				break;
			}
			case World::State::Boss:
			{
				auto& hero_pos = EntityController<Hero>::Position( model.hero );
				EntityController<Boss>::Update( model.boss, model, hero_pos, dt );
				GridController::AddObject( model.grid, &model.boss );

				if( EntityController<Boss>::Health( model.boss ) <= 0.f )
				{
					GameController::IncrementScore( game, 1000 );
					model.state = World::State::LevelComplete;
				}
				break;
			}
		}
	}

	void WorldController::Reset( World& model )noexcept
	{
		model.enemy_bullets = std::vector<Ammo>{};
		model.enemies = std::vector<Enemy>{};
		model.hero_bullets = std::vector<Ammo>{};
		model.asteroids = std::vector<Asteroid>{};
		EntityController<Hero>::Reset( model.hero );
		model.state = World::State::Arena;
		LevelController::Reset( model.level );
		EntityController<Boss>::Reset( model.boss );
	}

	int WorldController::CurrentLevelIndex( World const & model ) noexcept
	{
		return LevelController::CurrentLevelIndex( model.level ) - 1;
	}

	void WorldController::DoCollisions( World & model, Game & game ) noexcept
	{
		auto dispatch = [ & ]( auto* objectA, auto* objectB )
		{
			DoCollision( *objectA, *objectB, game );
		};

		for( auto& cell : GridController::Cells( model.grid ) )
		{
			auto& variants = CellController::Objects( cell );

			for( int i = 0; i < variants.size(); ++i )
			{
				for( int j = i + 1; j < variants.size(); ++j )
				{
					std::visit( dispatch, variants[ i ], variants[ j ] );
				}
			}
		}
	}

	void WorldController::SpawnAsteroid( World& model, Asteroid const& asteroid )
	{
		model.asteroids.emplace_back( asteroid );
	}

	void WorldController::SpawnEnemy( World& model, Enemy enemy_ )
	{
		model.enemies.emplace_back( std::move( enemy_ ) );
	}

	void WorldController::SpawnAmmo( World& model, Ammo const & ammo )
	{
		EntityController<Ammo>::AABB( ammo );

		if( EntityController<Ammo>::GetOwner( ammo ) == Ammo::Owner::Enemy )
			model.enemy_bullets.emplace_back( ammo );
		else
			model.hero_bullets.emplace_back( ammo );
	}

	bool WorldController::HeroWon( World const & model ) noexcept
	{
		return model.state == World::State::HeroWon;
	}

	bool WorldController::HeroLost( World const & model ) noexcept
	{
		return model.state == World::State::HeroLost;
	}

	void WorldController::RemoveDeadBullets( World& model ) noexcept
	{
		auto ammo_is_dead = [ & ]( Ammo const& bullet )
		{
			return !EntityController<Ammo>::IsAlive( bullet );
		};

		erase_if( model.hero_bullets, ammo_is_dead );
		erase_if( model.enemy_bullets, ammo_is_dead );
	}

	void WorldController::RemoveDeadEnemies( World& model ) noexcept
	{
		auto enemy_is_dead = [ & ]( Enemy const& enemy_ )
		{
			return !EntityController<Enemy>::IsAlive( enemy_ );
		};

		erase_if( model.enemies, enemy_is_dead );
	}

	void WorldController::RemoveDeadAsteroids( World& model ) noexcept
	{
		std::vector<Vec2> positions;
		positions.reserve( model.asteroids.size() );

		erase_if( model.asteroids, [ & ]( Asteroid const& astro )
		{
			if( EntityController<Asteroid>::Health( astro ) > 0.f ) return false;

			if( EntityController<Asteroid>::Reason( astro ) !=
				Asteroid::DeathReason::LeftScreen ) return false;

			if( !EntityController<Asteroid>::IsBigAsteroid( astro ) ) return false;

			positions.push_back( EntityController<Asteroid>::Position( astro ) );

			return true;
		} );

		constexpr auto nw = Vec2{ -.707f, -.707f };
		constexpr auto ne = Vec2{ .707f, -.707f };
		constexpr auto sw = Vec2{ -.707f,  .707f };
		constexpr auto se = Vec2{ .707f,  .707f };

		auto spawn = [ & ]( const auto& position, const auto& direction ) {
			const auto spawn_pos = position + ( direction * BigAsteroid::radius );
			SpawnAsteroid( model, Asteroid{ spawn_pos, direction, SmallAsteroid{} } );
		};

		for( auto const& position : positions )
		{
			spawn( position, nw );
			spawn( position, ne );
			spawn( position, sw );
			spawn( position, se );
		}
	}

	void WorldController::DoCollision( Asteroid& lhs, Asteroid& rhs, Game& game )noexcept
	{
		const auto lRect = EntityController<Asteroid>::AABB( lhs );
		const auto rRect = EntityController<Asteroid>::AABB( rhs );

		if( !RectController::Overlaps( lRect, rRect ) ) return;

		EntityController<Asteroid>::TakeDamage( lhs, EntityController<Asteroid>::Damage( rhs ) );
		EntityController<Asteroid>::TakeDamage( rhs, EntityController<Asteroid>::Damage( lhs ) );

		if( EntityController<Asteroid>::Health( lhs ) <= 0.f )
			EntityController<Asteroid>::Reason( lhs, Asteroid::DeathReason::AffectedByAsteroid );
		if( EntityController<Asteroid>::Health( rhs ) <= 0.f )
			EntityController<Asteroid>::Reason( rhs, Asteroid::DeathReason::AffectedByAsteroid );
	}
	void WorldController::DoCollision( Asteroid& lhs, Ammo& rhs, Game& game )noexcept
	{
		const auto lRect = EntityController<Asteroid>::AABB( lhs );
		const auto rRect = EntityController<Ammo>::AABB( rhs );

		if( !RectController::Overlaps( lRect, rRect ) ) return;

		EntityController<Asteroid>::TakeDamage( lhs, EntityController<Ammo>::Damage( rhs ) );
		EntityController<Ammo>::TakeDamage( rhs, EntityController<Asteroid>::Damage( lhs ) );

		if( EntityController<Asteroid>::Health( lhs ) > 0.f ) return;

		const auto reason = EntityController<Ammo>::GetOwner( rhs ) == Ammo::Owner::Hero ?
			Asteroid::DeathReason::AffectedByPlayer :
			Asteroid::DeathReason::AffectedByEnemy;

		EntityController<Asteroid>::Reason( lhs, reason );

		if( EntityController<Ammo>::GetOwner( rhs ) == Ammo::Owner::Hero )
			GameController::IncrementScore( game, EntityController<Asteroid>::ScoreValue( lhs ) );
	}
	void WorldController::DoCollision( Asteroid& lhs, Enemy& rhs, Game& game )noexcept
	{
		const auto lRect = EntityController<Asteroid>::AABB( lhs );
		const auto rRect = EntityController<Enemy>::AABB( rhs );

		if( !RectController::Overlaps( lRect, rRect ) ) return;

		EntityController<Asteroid>::TakeDamage( lhs, EntityController<Enemy>::Damage( rhs ) );
		EntityController<Enemy>::TakeDamage( rhs, EntityController<Asteroid>::Damage( lhs ) );

		if( EntityController<Asteroid>::Health( lhs ) > 0.f ) return;

		EntityController<Asteroid>::Reason( lhs, Asteroid::DeathReason::AffectedByEnemy );
	}
	void WorldController::DoCollision( Asteroid& lhs, Hero& rhs, Game& game )noexcept
	{
		const auto lRect = EntityController<Asteroid>::AABB( lhs );
		const auto rRect = EntityController<Hero>::AABB( rhs );

		if( !RectController::Overlaps( lRect, rRect ) ) return;

		EntityController<Asteroid>::TakeDamage( lhs, EntityController<Hero>::Damage( rhs ) );
		EntityController<Hero>::TakeDamage( rhs, EntityController<Asteroid>::Damage( lhs ) );
		if( EntityController<Asteroid>::Health( lhs ) > 0.f ) return;

		GameController::IncrementScore( game, EntityController<Asteroid>::ScoreValue( lhs ) );
		EntityController<Asteroid>::Reason( lhs, Asteroid::DeathReason::AffectedByPlayer );
	}
	void WorldController::DoCollision( Ammo& lhs, Asteroid& rhs, Game& game )noexcept
	{
		const auto lRect = EntityController<Ammo>::AABB( lhs );
		const auto rRect = EntityController<Asteroid>::AABB( rhs );

		if( !RectController::Overlaps( lRect, rRect ) ) return;

		EntityController<Asteroid>::TakeDamage( rhs, EntityController<Ammo>::Damage( lhs ) );
		EntityController<Ammo>::TakeDamage( lhs, EntityController<Asteroid>::Damage( rhs ) );

		if( EntityController<Asteroid>::Health( rhs ) > 0.f ) return;

		auto reason = ( EntityController<Ammo>::GetOwner( lhs ) == Ammo::Owner::Hero ?
			Asteroid::DeathReason::AffectedByPlayer :
			Asteroid::DeathReason::AffectedByEnemy );

		EntityController<Asteroid>::Reason( rhs, reason );

		if( EntityController<Ammo>::GetOwner( lhs ) == Ammo::Owner::Hero )
		{
			GameController::IncrementScore( game, EntityController<Asteroid>::ScoreValue( rhs ) );
		}
	}
	void WorldController::DoCollision( Ammo& lhs, Boss& rhs, Game& game )noexcept
	{
		if( EntityController<Ammo>::GetOwner( lhs ) == Ammo::Owner::Enemy )return;

		const auto lRect = EntityController<Ammo>::AABB( lhs );
		const auto rRect = EntityController<Boss>::AABB( rhs );

		if( !RectController::Overlaps( lRect, rRect ) ) return;

		EntityController<Ammo>::TakeDamage( lhs, EntityController<Boss>::Damage( rhs ) );
		EntityController<Boss>::TakeDamage( rhs, EntityController<Ammo>::Damage( lhs ) );
	}
	void WorldController::DoCollision( Ammo& lhs, Enemy& rhs, Game& game )noexcept
	{
		if( EntityController<Ammo>::GetOwner( lhs ) == Ammo::Owner::Enemy )return;

		const auto lRect = EntityController<Ammo>::AABB( lhs );
		const auto rRect = EntityController<Enemy>::AABB( rhs );

		if( !RectController::Overlaps( lRect, rRect ) ) return;

		EntityController<Ammo>::TakeDamage( lhs, EntityController<Enemy>::Damage( rhs ) );
		EntityController<Enemy>::TakeDamage( rhs, EntityController<Ammo>::Damage( lhs ) );

		if( EntityController<Enemy>::Health( rhs ) > 0.f ) return;

		GameController::IncrementScore( game, Enemy::score_value );
	}
	void WorldController::DoCollision( Ammo& lhs, Hero& rhs, Game& game )noexcept
	{
		if( EntityController<Ammo>::GetOwner( lhs ) == Ammo::Owner::Hero )return;

		const auto lRect = EntityController<Ammo>::AABB( lhs );
		const auto rRect = EntityController<Hero>::AABB( rhs );

		if( !RectController::Overlaps( lRect, rRect ) ) return;

		EntityController<Ammo>::TakeDamage( lhs, EntityController<Hero>::Damage( rhs ) );
		EntityController<Hero>::TakeDamage( rhs, EntityController<Ammo>::Damage( lhs ) );
	}
	void WorldController::DoCollision( Boss& lhs, Ammo& rhs, Game& game )noexcept
	{
		if( EntityController<Ammo>::GetOwner( rhs ) == Ammo::Owner::Enemy ) return;

		const auto lRect = EntityController<Boss>::AABB( lhs );
		const auto rRect = EntityController<Ammo>::AABB( rhs );

		if( !RectController::Overlaps( lRect, rRect ) ) return;

		EntityController<Boss>::TakeDamage( lhs, EntityController<Ammo>::Damage( rhs ) );
		EntityController<Ammo>::TakeDamage( rhs, EntityController<Boss>::Damage( lhs ) );
	}
	void WorldController::DoCollision( Boss& lhs, Hero& rhs, Game& game )noexcept
	{
		const auto lRect = EntityController<Boss>::AABB( lhs );
		const auto rRect = EntityController<Hero>::AABB( rhs );

		if( !RectController::Overlaps( lRect, rRect ) ) return;

		EntityController<Boss>::TakeDamage( lhs, EntityController<Hero>::Damage( rhs ) );
		EntityController<Hero>::TakeDamage( rhs, EntityController<Boss>::Damage( lhs ) );
	}
	void WorldController::DoCollision( Enemy& lhs, Asteroid& rhs, Game& game )noexcept
	{
		const auto lRect = EntityController<Enemy>::AABB( lhs );
		const auto rRect = EntityController<Asteroid>::AABB( rhs );

		if( !RectController::Overlaps( lRect, rRect ) ) return;

		EntityController<Enemy>::TakeDamage( lhs, EntityController<Asteroid>::Damage( rhs ) );
		EntityController<Asteroid>::TakeDamage( rhs, EntityController<Enemy>::Damage( lhs ) );

		if( EntityController<Asteroid>::Health( rhs ) > 0.f ) return;

		EntityController<Asteroid>::Reason( rhs, Asteroid::DeathReason::AffectedByEnemy );
	}
	void WorldController::DoCollision( Enemy& lhs, Ammo& rhs, Game& game )noexcept
	{
		if( EntityController<Ammo>::GetOwner( rhs ) == Ammo::Owner::Enemy )return;

		const auto lRect = EntityController<Enemy>::AABB( lhs );
		const auto rRect = EntityController<Ammo>::AABB( rhs );

		if( !RectController::Overlaps( lRect, rRect ) ) return;

		EntityController<Enemy>::TakeDamage( lhs, EntityController<Ammo>::Damage( rhs ) );
		EntityController<Ammo>::TakeDamage( rhs, EntityController<Enemy>::Damage( lhs ) );

		if( EntityController<Enemy>::Health( lhs ) > 0.f ) return;

		GameController::IncrementScore( game, Enemy::score_value );
	}
	void WorldController::DoCollision( Enemy& lhs, Hero& rhs, Game& game )noexcept
	{
		const auto lRect = EntityController<Enemy>::AABB( lhs );
		const auto rRect = EntityController<Hero>::AABB( rhs );

		if( !RectController::Overlaps( lRect, rRect ) ) return;

		EntityController<Enemy>::TakeDamage( lhs, EntityController<Hero>::Damage( rhs ) );
		EntityController<Hero>::TakeDamage( rhs, EntityController<Enemy>::Damage( lhs ) );

		if( EntityController<Enemy>::Health( lhs ) > 0.f ) return;

		GameController::IncrementScore( game, Enemy::score_value );
	}
	void WorldController::DoCollision( Hero& lhs, Asteroid& rhs, Game& game )noexcept
	{
		const auto lRect = EntityController<Hero>::AABB( lhs );
		const auto rRect = EntityController<Asteroid>::AABB( rhs );

		if( !RectController::Overlaps( lRect, rRect ) ) return;

		EntityController<Hero>::TakeDamage( lhs, EntityController<Asteroid>::Damage( rhs ) );
		EntityController<Asteroid>::TakeDamage( rhs, EntityController<Hero>::Damage( lhs ) );

		if( EntityController<Asteroid>::Health( rhs ) > 0.f ) return;

		GameController::IncrementScore( game, EntityController<Asteroid>::ScoreValue( rhs ) );
		EntityController<Asteroid>::Reason( rhs, Asteroid::DeathReason::AffectedByPlayer );
	}
	void WorldController::DoCollision( Hero& lhs, Ammo& rhs, Game& game )noexcept
	{
		if( EntityController<Ammo>::GetOwner( rhs ) == Ammo::Owner::Hero )return;

		const auto lRect = EntityController<Hero>::AABB( lhs );
		const auto rRect = EntityController<Ammo>::AABB( rhs );

		if( !RectController::Overlaps( lRect, rRect ) ) return;

		EntityController<Hero>::TakeDamage( lhs, EntityController<Ammo>::Damage( rhs ) );
		EntityController<Ammo>::TakeDamage( rhs, EntityController<Hero>::Damage( lhs ) );
	}
	void WorldController::DoCollision( Hero& lhs, Boss& rhs, Game& game )noexcept
	{
		const auto lRect = EntityController<Hero>::AABB( lhs );
		const auto rRect = EntityController<Boss>::AABB( rhs );

		if( !RectController::Overlaps( lRect, rRect ) ) return;

		EntityController<Hero>::TakeDamage( lhs, EntityController<Boss>::Damage( rhs ) );
		EntityController<Boss>::TakeDamage( rhs, EntityController<Hero>::Damage( lhs ) );
	}
	void WorldController::DoCollision( Hero& lhs, Enemy& rhs, Game& game )noexcept
	{
		const auto lRect = EntityController<Hero>::AABB( lhs );
		const auto rRect = EntityController<Enemy>::AABB( rhs );

		if( !RectController::Overlaps( lRect, rRect ) ) return;

		EntityController<Hero>::TakeDamage( lhs, EntityController<Enemy>::Damage( rhs ) );
		EntityController<Enemy>::TakeDamage( rhs, EntityController<Hero>::Damage( lhs ) );

		if( EntityController<Enemy>::Health( rhs ) > 0.f ) return;

		GameController::IncrementScore( game, Enemy::score_value );
	}
}
