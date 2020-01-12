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
#include "LevelController.h"

namespace sns
{
	void WorldController::Update( World& model, Keyboard& kbd, Game& game, float dt )
	{
		Grid::Controller::ClearCells( model.grid );

		for( auto& star : model.stars ) Star::Controller::Update( star );
		
		Hero::Controller::Update( model.hero, model, kbd, dt );
		Grid::Controller::AddObject( model.grid, model.hero );

		for( auto& ammo : model.hero_bullets )
		{
			Ammo::Controller::Update( ammo, dt );
			Grid::Controller::AddObject( model.grid, ammo );
		}

		for( auto& ammo : model.enemy_bullets )
		{
			Ammo::Controller::Update( ammo, dt );
			Grid::Controller::AddObject( model.grid, ammo );
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
					Enemy::Controller::Update( enemy, dt );
					Grid::Controller::AddObject( model.grid, enemy );
				}

				for( auto& astro : model.asteroids ) 
				{
					Asteroid::Controller::Update( astro, dt );
					Grid::Controller::AddObject( model.grid, astro );
				}

				if( Level::Controller::AsteroidSpawnerComplete( model.level ) &&
					Level::Controller::EnemySpawnerComplete( model.level ) )
				{
					model.state = World::State::Boss;
					model.boss = Level::Controller::SpawnBoss( model.level );
					Grid::Controller::AddObject( model.grid, model.boss );
				}

				if( Hero::Controller::Health( model.hero ) <= 0.f )
					model.state = World::State::HeroLost;

				break;
			}
			case World::State::LevelComplete:
			{
				if( !Level::Controller::IsFinal( model.level ) )
				{
					Level::Controller::Advance( model.level );
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
				Boss::Controller::Update( model.boss, model, dt );
				Grid::Controller::AddObject( model.grid, model.boss );

				if( Boss::Controller::Health( model.boss ) <= 0.f )
				{
					Game::Controller::IncrementScore( game, 1000 );
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
		model.hero.Reset();
		model.state = World::State::Arena;
		model.level.Reset();
		model.boss.Reset();
	}

	int WorldController::CurrentLevelIndex( World const & model ) noexcept
	{
		return Level::Controller::CurrentLevelIndex( model.level ) - 1;
	}

	void WorldController::DoCollisions( World & model, Game & game ) noexcept
	{
		auto dispatch = [ & ]( auto* objectA, auto* objectB )
		{
			DoCollision( *objectA, *objectB, game );
		};

		for( auto& cell : Grid::Controller::Cells( model.grid ) )
		{
			auto& variants = cell.Objects();
			for( int i = 0; i < variants.size(); ++i )
			{
				for( int j = i + 1; i < variants.size(); ++j )
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
		Ammo::Controller::AABB( ammo );

		if( Ammo::Controller::GetOwner( ammo ) == Ammo::Owner::Enemy )
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
		auto ammo_is_dead = 
			[ & ]( Ammo const& bullet ) { return !Ammo::Controller::IsAlive( bullet ); };

		erase_if( model.hero_bullets, ammo_is_dead );
		erase_if( model.enemy_bullets, ammo_is_dead );
	}

	void WorldController::RemoveDeadEnemies( World& model ) noexcept
	{
		auto enemy_is_dead =
			[ & ]( Enemy const& enemy_ ) { return !Enemy::Controller::IsAlive( enemy_ ); };

		erase_if( model.enemies, enemy_is_dead );
	}

	void WorldController::RemoveDeadAsteroids( World& model ) noexcept
	{
		std::vector<Vec2> positions;
		positions.reserve( model.asteroids.size() );

		erase_if( model.asteroids, [ & ]( Asteroid const& astro ) 
		{
			if( Asteroid::Controller::Health( astro ) > 0.f ) return false;
			
			if( Asteroid::Controller::Reason( astro ) != 
				Asteroid::DeathReason::LeftScreen ) return false;

			if( !Asteroid::Controller::IsBigAsteroid( astro ) ) return false;

			positions.push_back( Asteroid::Controller::Position( astro ) );

			return true;
		} );

		constexpr auto nw = Vec2{ -.707f, -.707f };
		constexpr auto ne = Vec2{  .707f, -.707f };
		constexpr auto sw = Vec2{ -.707f,  .707f };
		constexpr auto se = Vec2{  .707f,  .707f };

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
		const auto lRect = Asteroid::Controller::AABB( lhs );
		const auto rRect = Asteroid::Controller::AABB( rhs );

		if( !lRect.Overlaps( rRect ) ) return;

		Asteroid::Controller::TakeDamage( lhs, Asteroid::Controller::Damage( rhs ) );
		Asteroid::Controller::TakeDamage( rhs, Asteroid::Controller::Damage( lhs ) );

		if( Asteroid::Controller::Health( lhs ) <= 0.f )
			Asteroid::Controller::Reason( lhs, Asteroid::DeathReason::AffectedByAsteroid );
		if( Asteroid::Controller::Health( rhs ) <= 0.f )
			Asteroid::Controller::Reason( rhs, Asteroid::DeathReason::AffectedByAsteroid );
	}
	void WorldController::DoCollision( Asteroid& lhs, Ammo& rhs, Game& game )noexcept
	{
		const auto lRect = Asteroid::Controller::AABB( lhs );
		const auto rRect = Ammo::Controller::AABB( rhs );

		if( !lRect.Overlaps( rRect ) ) return;

		Asteroid::Controller::TakeDamage( lhs, Ammo::Controller::Damage( rhs ) );
		Ammo::Controller::TakeDamage( rhs, Asteroid::Controller::Damage( lhs ) );

		if( Asteroid::Controller::Health( lhs ) > 0.f ) return;

		const auto reason = Ammo::Controller::GetOwner( rhs ) == Ammo::Owner::Hero ?
			Asteroid::DeathReason::AffectedByPlayer :
			Asteroid::DeathReason::AffectedByEnemy;

		Asteroid::Controller::Reason( lhs, reason );

		if( Ammo::Controller::GetOwner( rhs ) == Ammo::Owner::Hero )
			GameController::IncrementScore( game, Asteroid::Controller::ScoreValue( lhs ) );
	}
	void WorldController::DoCollision( Asteroid& lhs, Enemy& rhs, Game& game )noexcept
	{
		const auto lRect = Asteroid::Controller::AABB( lhs );
		const auto rRect = Enemy::Controller::AABB( rhs );

		if( !lRect.Overlaps( rRect ) ) return;

		Asteroid::Controller::TakeDamage( lhs, Enemy::Controller::Damage( rhs ) );
		Enemy::Controller::TakeDamage( rhs, Asteroid::Controller::Damage( lhs ) );

		if( Asteroid::Controller::Health( lhs ) > 0.f ) return;

		Asteroid::Controller::Reason( lhs, Asteroid::DeathReason::AffectedByEnemy );
	}
	void WorldController::DoCollision( Asteroid& lhs, Hero& rhs, Game& game )noexcept
	{
		const auto lRect = Asteroid::Controller::AABB( lhs );
		const auto rRect = Hero::Controller::AABB( rhs );

		if( !lRect.Overlaps( rRect ) ) return;

		Asteroid::Controller::TakeDamage( lhs, Hero::Controller::Damage( rhs ) );
		Hero::Controller::TakeDamage( rhs, Asteroid::Controller::Damage( lhs ) );
		if( Asteroid::Controller::Health( lhs ) > 0.f ) return;

		GameController::IncrementScore( game, Asteroid::Controller::ScoreValue( lhs ) );
		Asteroid::Controller::Reason( lhs, Asteroid::DeathReason::AffectedByPlayer );
	}
	void WorldController::DoCollision( Ammo& lhs, Asteroid& rhs, Game& game )noexcept
	{
		const auto lRect = Ammo::Controller::AABB( lhs );
		const auto rRect = Asteroid::Controller::AABB( rhs );

		if( !lRect.Overlaps( rRect ) ) return;

		Asteroid::Controller::TakeDamage( rhs, Ammo::Controller::Damage( lhs ) );
		Ammo::Controller::TakeDamage( lhs, Asteroid::Controller::Damage( rhs ) );

		if( Asteroid::Controller::Health( rhs ) > 0.f ) return;

		auto reason = ( Ammo::Controller::GetOwner( lhs ) == Ammo::Owner::Hero ?
			Asteroid::DeathReason::AffectedByPlayer :
			Asteroid::DeathReason::AffectedByEnemy );

		Asteroid::Controller::Reason( rhs, reason );

		if( Ammo::Controller::GetOwner( lhs ) == Ammo::Owner::Hero )
		{
			Game::Controller::IncrementScore( game, Asteroid::Controller::ScoreValue( rhs ) );
		}
	}
	void WorldController::DoCollision( Ammo& lhs, Boss& rhs, Game& game )noexcept
	{
		if( Ammo::Controller::GetOwner( lhs ) == Ammo::Owner::Enemy )return;

		const auto lRect = Ammo::Controller::AABB( lhs );
		const auto rRect = Boss::Controller::AABB( rhs );

		if( !lRect.Overlaps( rRect ) ) return;

		Ammo::Controller::TakeDamage( lhs, Boss::Controller::Damage( rhs ) );
		Boss::Controller::TakeDamage( rhs, Ammo::Controller::Damage( lhs ) );
	}
	void WorldController::DoCollision( Ammo& lhs, Enemy& rhs, Game& game )noexcept
	{
		if( Ammo::Controller::GetOwner( lhs ) == Ammo::Owner::Enemy )return;

		const auto lRect = Ammo::Controller::AABB( lhs );
		const auto rRect = Enemy::Controller::AABB( rhs );

		if( !lRect.Overlaps( rRect ) ) return;

		Ammo::Controller::TakeDamage( lhs, Enemy::Controller::Damage( rhs ) );
		Enemy::Controller::TakeDamage( rhs, Ammo::Controller::Damage( lhs ) );
		
		if( Enemy::Controller::Health( rhs ) > 0.f ) return;

		Game::Controller::IncrementScore( game, Enemy::score_value );
	}
	void WorldController::DoCollision( Ammo& lhs, Hero& rhs, Game& game )noexcept
	{
		if( Ammo::Controller::GetOwner( lhs ) == Ammo::Owner::Hero )return;

		const auto lRect = Ammo::Controller::AABB( lhs );
		const auto rRect = Hero::Controller::AABB( rhs );

		if( !lRect.Overlaps( rRect ) ) return;

		Ammo::Controller::TakeDamage( lhs, Hero::Controller::Damage( rhs ) );
		Hero::Controller::TakeDamage( rhs, Ammo::Controller::Damage( lhs ) );
	}
	void WorldController::DoCollision( Boss& lhs, Ammo& rhs, Game& game )noexcept
	{
		if( Ammo::Controller::GetOwner( rhs ) == Ammo::Owner::Enemy ) return;

		const auto lRect = Boss::Controller::AABB( lhs );
		const auto rRect = Ammo::Controller::AABB( rhs );

		if( !lRect.Overlaps( rRect ) ) return;

		Boss::Controller::TakeDamage( lhs, Ammo::Controller::Damage( rhs ) );
		Ammo::Controller::TakeDamage( rhs, Boss::Controller::Damage( lhs ) );
	}
	void WorldController::DoCollision( Boss& lhs, Hero& rhs, Game& game )noexcept
	{
		const auto lRect = Boss::Controller::AABB( lhs );
		const auto rRect = Hero::Controller::AABB( rhs );

		if( !lRect.Overlaps( rRect ) ) return;

		Boss::Controller::TakeDamage( lhs, Hero::Controller::Damage( rhs ) );
		Hero::Controller::TakeDamage( rhs, Boss::Controller::Damage( lhs ) );
	}
	void WorldController::DoCollision( Enemy& lhs, Asteroid& rhs, Game& game )noexcept
	{
		const auto lRect = Enemy::Controller::AABB( lhs );
		const auto rRect = Asteroid::Controller::AABB( rhs );

		if( !lRect.Overlaps( rRect ) ) return;

		Enemy::Controller::TakeDamage( lhs, Asteroid::Controller::Damage( rhs ) );
		Asteroid::Controller::TakeDamage( rhs, Enemy::Controller::Damage( lhs ) );

		if( Asteroid::Controller::Health( rhs ) > 0.f ) return;

		Asteroid::Controller::Reason( rhs, Asteroid::DeathReason::AffectedByEnemy );
	}
	void WorldController::DoCollision( Enemy& lhs, Ammo& rhs, Game& game )noexcept
	{
		if( Ammo::Controller::GetOwner( rhs ) == Ammo::Owner::Enemy )return;

		const auto lRect = Enemy::Controller::AABB( lhs );
		const auto rRect = Ammo::Controller::AABB( rhs );

		if( !lRect.Overlaps( rRect ) ) return;

		Enemy::Controller::TakeDamage( lhs, Ammo::Controller::Damage( rhs ) );
		Ammo::Controller::TakeDamage( rhs, Enemy::Controller::Damage( lhs ) );

		if( Enemy::Controller::Health( lhs ) > 0.f ) return;

		Game::Controller::IncrementScore( game, Enemy::score_value );
	}
	void WorldController::DoCollision( Enemy& lhs, Hero& rhs, Game& game )noexcept
	{
		const auto lRect = Enemy::Controller::AABB( lhs );
		const auto rRect = Hero::Controller::AABB( rhs );

		if( !lRect.Overlaps( rRect ) ) return;

		Enemy::Controller::TakeDamage( lhs, Hero::Controller::Damage( rhs ) );
		Hero::Controller::TakeDamage( rhs, Enemy::Controller::Damage( lhs ) );

		if( Enemy::Controller::Health( lhs ) > 0.f ) return;
		
		Game::Controller::IncrementScore( game, Enemy::score_value );
	}
	void WorldController::DoCollision( Hero& lhs, Asteroid& rhs, Game& game )noexcept
	{
		const auto lRect = Hero::Controller::AABB( lhs );
		const auto rRect = Asteroid::Controller::AABB( rhs );

		if( !lRect.Overlaps( rRect ) ) return;

		Hero::Controller::TakeDamage( lhs, Asteroid::Controller::Damage( rhs ) );
		Asteroid::Controller::TakeDamage( rhs, Hero::Controller::Damage( lhs ) );

		if( Asteroid::Controller::Health( rhs ) > 0.f ) return;

		GameController::IncrementScore( game, Asteroid::Controller::ScoreValue( rhs ) );
		Asteroid::Controller::Reason( rhs, Asteroid::DeathReason::AffectedByPlayer );
	}
	void WorldController::DoCollision( Hero& lhs, Ammo& rhs, Game& game )noexcept
	{
		if( Ammo::Controller::GetOwner( rhs ) == Ammo::Owner::Hero )return;

		const auto lrect = Hero::Controller::AABB( lhs );
		const auto rrect = Ammo::Controller::AABB( rhs );

		if( !lrect.Overlaps( rrect ) ) return;

		Hero::Controller::TakeDamage( lhs, Ammo::Controller::Damage( rhs ) );
		Ammo::Controller::TakeDamage( rhs, Hero::Controller::Damage( lhs ) );
	}
	void WorldController::DoCollision( Hero& lhs, Boss& rhs, Game& game )noexcept
	{
		const auto lRect = Hero::Controller::AABB( lhs );
		const auto rRect = Boss::Controller::AABB( rhs );

		if( !lRect.Overlaps( rRect ) ) return;

		Hero::Controller::TakeDamage( lhs, Boss::Controller::Damage( rhs ) );
		Boss::Controller::TakeDamage( rhs, Hero::Controller::Damage( lhs ) );
	}
	void WorldController::DoCollision( Hero& lhs, Enemy& rhs, Game& game )noexcept
	{
		const auto lRect = Hero::Controller::AABB(  lhs );
		const auto rRect = Enemy::Controller::AABB( rhs );

		if( !lRect.Overlaps( rRect ) ) return;

		Hero::Controller::TakeDamage( lhs, Enemy::Controller::Damage( rhs ) );
		Enemy::Controller::TakeDamage( rhs, Hero::Controller::Damage( lhs ) );

		if( Enemy::Controller::Health( rhs ) > 0.f ) return;

		Game::Controller::IncrementScore( game, Enemy::score_value );
	}
}
