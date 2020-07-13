#include "EnemyController.h"
#include "Enemies.h"
#include <type_traits>

namespace sns
{
	void EnemyController::Update( Enemy& model, float dt ) noexcept
	{
		auto do_update = [ & ]( auto& enemy_ )
		{
			using type = std::decay_t<decltype( enemy_ )>;
			constexpr auto minSqrDistFromWaypoint = sqr( type::aabb.Width() / 2.f );

			const auto delta = type::waypoints[ model.waypoint_index ] - model.position;
			if( delta.LengthSq() < minSqrDistFromWaypoint )
			{
				++model.waypoint_index;
				model.velocity = ( type::waypoints[ model.waypoint_index ] - model.position ).Normalize();
			}

			if( model.waypoint_index >= type::waypoints.size() )
			{
				model.health = 0.f;
			}
		};
		
		std::visit( do_update, model.variant );
	}

	void EnemyController::TakeDamage( Enemy& model, float amount ) noexcept
	{
		model.health -= amount;
	}

	RectF EnemyController::AABB( Enemy& model ) const noexcept
	{
		return std::visit( [ & ]( auto const& enemy_ )
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
		return std::visit( [ & ]( auto const& enemy_ ) {
			using type = std::decay_t<decltype( enemy_ )>;
			return type::damage;
		}, model.variant );
	}
}
