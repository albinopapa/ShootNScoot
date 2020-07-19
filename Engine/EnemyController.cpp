#include "EnemyController.h"
#include "WeaponController.h"
#include "ChiliMath.h"
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
	const auto& hero_position = world.hero.position;
	const auto delta = ( hero_position - parent.position );
	const auto sqrDistance = delta.LengthSq();

	// Arbitrarily made up line of sight
	constexpr auto line_of_sight = 250.f;

	switch( enemy.m_state )
	{
		case Enemy1::State::Scouting:
		{
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
				enemy.m_state = Enemy1::State::Turning;
			}
			break;
		}
		case Enemy1::State::Turning:
		{
			constexpr auto min_rotation = Radian{ -( pi * .5f ) };
			constexpr auto pi2 = Radian{ 2.f * pi };

			// If left of center, turn counterclockwise
			// If right of center, turn clockwise
			enemy.m_angle += ( parent.position.x < Graphics::GetRect<float>().Center().x ?
				Radian{ -.1f } : Radian{ .1f } );
			

			// If angle is greater than 180 wrap angle to -180 ( probably counting up )
			if( enemy.m_angle > pi ) enemy.m_angle -= pi2;
			// If angle is less than -180 wrap angle to 180 ( probably counting down )
			else if( enemy.m_angle < -pi ) enemy.m_angle += pi2;

			if( enemy.m_angle >= min_rotation - .05f && enemy.m_angle <= min_rotation + .05f )
			{
				enemy.m_state = Enemy1::State::Retreating;
				parent.velocity = Vec2{ 0.f, -1.f };
			}
			else 
			{
				parent.velocity = Vec2{ enemy.m_angle.Cos(), enemy.m_angle.Sin() };
			}

			break;
		}
		case Enemy1::State::Retreating:
		{
			// Fire at player while retreating
			if(WeaponController::CanFire(enemy.m_weapon))
			{
				WeaponController::Fire(
					enemy.m_weapon,
					parent.position,
					delta.Normalize(),
					world,
					AmmoOwner::Enemy
				);
			}
			break;
		}
	}

	if( !Graphics::IsVisible( RectI{ Enemy2::aabb + parent.position } ) &&
		parent.velocity.Dot( world.hero.position - parent.position ) < 0.f )
	{
		parent.health = 0.f;
	}
}
void EnemyController::Update( Enemy& parent, Enemy2& enemy, World& world, float dt ) noexcept
{
	switch( enemy.m_state )
	{
		case Enemy2::State::Drifting:
		{
			const auto delta = world.hero.position - parent.position;
			// Arbitrarily made up line of sight
			constexpr auto line_of_sight = 400.f;
			if( delta.LengthSq() < sqr( line_of_sight ) ) {
				parent.velocity = delta.Normalize() * 1.5f;
				enemy.m_angle = Radian{ std::atan2( parent.velocity.y, parent.velocity.x ) };
				enemy.m_state = Enemy2::State::Charging;
			}
			break;
		}
	}

	if( !Graphics::IsVisible( RectI{ Enemy2::aabb + parent.position } ) &&
		parent.velocity.Dot( world.hero.position - parent.position ) < 0.f )
	{
		parent.health = 0.f;
	}
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
