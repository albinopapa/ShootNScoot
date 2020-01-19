#include "AsteroidController.h"
#include "RectController.h"
#include "Settings.h"

namespace sns
{
	void EntityController<Asteroid>::Update( Asteroid& model, float dt ) noexcept
	{
		std::visit( [ & ]( auto& astro )
		{
			using type = std::decay_t<decltype( astro )>;

			model.position += ( model.direction * ( dt * Asteroid::speed ) );
			const auto aabb = type::aabb + model.position;
			
			if( ( ( aabb.bottom < 0.f				) && ( model.direction.y < 0.f ) ) ||
				( ( aabb.top	> world_rect.bottom ) && ( model.direction.y > 0.f ) ) ||
				( ( aabb.left   < 0.f				) && ( model.direction.x < 0.f ) ) ||
				( ( aabb.right  > world_rect.right  ) && ( model.direction.y > 0.f ) ) )
			{
				model.health = 0.f;
				model.reason = Asteroid::DeathReason::LeftScreen;
			}

		}, model.variant );
	}

	void EntityController<Asteroid>::TakeDamage( Asteroid& model, float amount ) noexcept
	{
		model.health -= amount;
	}

	void EntityController<Asteroid>::Reason( Asteroid& model, Asteroid::DeathReason reason ) noexcept
	{
		model.reason = reason;
	}

	RectF EntityController<Asteroid>::AABB( Asteroid const& model )noexcept
	{
		return std::visit( [ & ]( auto const& astro ) {
			using type = std::decay_t<decltype( astro )>;
			return type::aabb + model.position;
		}, model.variant );
	}

	Vec2 const & EntityController<Asteroid>::Position( Asteroid const & model ) noexcept
	{
		return model.position;
	}

	float EntityController<Asteroid>::Damage( Asteroid const& model )noexcept
	{
		return std::visit( [ & ]( auto const& astro ) {
			using type = std::decay_t<decltype( astro )>;
			return type::damage;
		}, model.variant );
	}

	float EntityController<Asteroid>::Health( Asteroid const& model )noexcept
	{
		return model.health;
	}

	bool EntityController<Asteroid>::IsBigAsteroid( Asteroid const & model ) noexcept
	{
		return std::holds_alternative<BigAsteroid>( model.variant );
	}

	Asteroid::DeathReason EntityController<Asteroid>::Reason( Asteroid const& model )noexcept
	{
		return model.reason;
	}

	int EntityController<Asteroid>::ScoreValue( Asteroid const& model )noexcept
	{
		return std::visit( [ & ]( auto const& astro ) {
			using type = std::decay_t<decltype( astro )>;
			return type::score_value;
		}, model.variant );
	}
}
