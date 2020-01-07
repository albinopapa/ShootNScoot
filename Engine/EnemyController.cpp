#include "EnemyController.h"
#include "Enemies.h"
#include "Utilities.h"
#include <type_traits>

namespace sns
{
	void EnemyController::Update( Enemy& model, float dt ) noexcept
	{
		auto do_update = [ & ]( auto& enemy_ )
		{
			using type = std::decay_t<decltype( enemy_ )>;
			constexpr auto minSqrDistFromWaypoint = sqr( type::aabb.Width() / 2.f );

			if( const auto delta = model.waypoints[ model.waypoint_index ] - model.position; 
				delta.LengthSq() < minSqrDistFromWaypoint )
			{
				++model.waypoint_index;
			}

			if( model.waypoint_index < model.waypoints.Count() )
			{
				model.velocity = 
					( model.waypoints[ model.waypoint_index ] - model.position ).Normalize();
				model.angle = std::atan2( -model.velocity.y, model.velocity.x );
			}
		};

		std::visit( do_update, model.variant );
	}

	void EnemyController::TakeDamage( Enemy& model, float amount ) noexcept
	{
		model.health -= amount;
	}

	RectF EnemyController::AABB( Enemy const& model ) noexcept
	{
		return std::visit( [ & ]( auto const& enemy_ )
		{
			using type = std::decay_t<decltype( enemy_ )>;
			return type::aabb + model.position;
		}, model.variant );
	}

	float EnemyController::Health( Enemy const& model ) noexcept
	{
		return model.health;
	}

	float EnemyController::Damage( Enemy const& model ) noexcept
	{
		return std::visit( [ & ]( auto const& enemy_ ) {
			using type = std::decay_t<decltype( enemy_ )>;
			return type::damage;
		}, model.variant );
	}

	bool EnemyController::IsAlive( Enemy const& model ) noexcept
	{
		return model.waypoint_index < int( model.waypoints.Count() ) ||
			model.health <= 0.f;
	}
}
