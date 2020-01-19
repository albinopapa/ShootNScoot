#include "Enemies.h"
#include "EnemyController.h"
#include "RectController.h"
#include "Utilities.h"
#include "Vec2Controller.h"
#include <type_traits>

namespace sns
{
	void EntityController<Enemy>::Update( Enemy& model, float dt ) noexcept
	{
		std::visit( [ & ]( auto& enemy_ )
		{
			using type = std::decay_t<decltype( enemy_ )>;

			model.position += ( model.velocity * ( type::speed * dt ) );

			constexpr auto minSqrDistFromWaypoint =
				sqr( RectController::Width( type::aabb ) / 2.f );

			if( const auto delta = model.waypoints[ model.waypoint_index ] - model.position;
				Vec2Controller::LengthSq( delta ) < minSqrDistFromWaypoint )
			{
				++model.waypoint_index;
			}

			if( model.waypoint_index >= model.waypoints.Count() ) return;

			const auto delta = model.waypoints[ model.waypoint_index ] - model.position;
			model.velocity = Vec2Controller::Normalize( delta );
			model.angle = std::atan2( -model.velocity.y, model.velocity.x );

		}, model.variant );
	}

	void EntityController<Enemy>::TakeDamage( Enemy& model, float amount ) noexcept
	{
		model.health -= amount;
	}

	RectF EntityController<Enemy>::AABB( Enemy const& model ) noexcept
	{
		return std::visit( [ & ]( auto const& enemy_ )
		{
			using type = std::decay_t<decltype( enemy_ )>;
			return type::aabb + model.position;
		}, model.variant );
	}

	float EntityController<Enemy>::Health( Enemy const& model ) noexcept
	{
		return model.health;
	}

	float EntityController<Enemy>::Damage( Enemy const& model ) noexcept
	{
		return std::visit( [ & ]( auto const& enemy_ ) {
			using type = std::decay_t<decltype( enemy_ )>;
			return type::damage;
		}, model.variant );
	}

	bool EntityController<Enemy>::IsAlive( Enemy const& model ) noexcept
	{
		return model.waypoint_index < model.waypoints.Count() || model.health > 0.f;
	}

	Vec2 const & EntityController<Enemy>::Position( Enemy const & model ) noexcept
	{
		return model.position;
	}
}
