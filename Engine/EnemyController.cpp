#include "EnemyController.h"
#include "WeaponController.h"
#include <type_traits>

void EnemyController::Update( Enemy& model, World& world, float dt ) noexcept
{
	std::visit( [&]( auto& enemy_ ) { Update( model, enemy_, world, dt ); }, model.variant );
}

void EnemyController::TakeDamage( Enemy& model, float amount ) noexcept
{
	model.health -= amount;
}

RectF EnemyController::AABB( Enemy& model ) const noexcept
{
	return std::visit( [&]( auto const& enemy_ )
	{
		using type = std::decay_t<decltype( enemy_ )>;
		return type::aabb + model.position;
	}, model.variant );
}

float EnemyController::Health( Enemy& model ) const noexcept
{
	return model.health;
}

float EnemyController::Damage( Enemy& model ) const noexcept
{
	return std::visit( [&]( auto const& enemy_ ) {
		using type = std::decay_t<decltype( enemy_ )>;
		return type::damage;
	}, model.variant );
}
void EnemyController::Update( Enemy& parent, Enemy1& enemy, World& world, float dt ) noexcept
{
	switch( enemy.m_state )
	{
		case Enemy1::State::Scouting:
		{
			const auto& hero_position = world.hero.position;
			const auto delta = ( hero_position - parent.position );
			const auto sqrDistance = delta.LengthSq();

			// Arbitrarily made up line of sight
			constexpr auto line_of_sight = 150.f;
			if( sqrDistance < sqr( line_of_sight ) )
			{
				// Fire at player
				WeaponController::Fire(
					enemy.m_weapon,
					parent.position,
					delta.Normalize(),
					world,
					AmmoOwner::Enemy
				);

				// Turn tail and run
				parent.velocity = { 0.f, -1.f };
				enemy.m_state = Enemy1::State::Retreating;
			}
			break;
		}
		case Enemy1::State::Retreating:
		{
			if( parent.position.y + enemy.aabb.bottom < 0.f )
			{
				parent.health = 0.f;
			}
			break;
		}
	}
}
void EnemyController::Update( Enemy& parent, Enemy2& enemy, World& world, float dt ) noexcept
{
}
void EnemyController::Update( Enemy& parent, Enemy3& enemy, World& world, float dt ) noexcept
{
}
void EnemyController::Update( Enemy& parent, Enemy4& enemy, World& world, float dt ) noexcept
{
}
void EnemyController::Update( Enemy& parent, Enemy5& enemy, World& world, float dt ) noexcept
{
}
