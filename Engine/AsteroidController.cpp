#include "AsteroidController.h"
#include "Graphics.h"

namespace sns
{
	void EntityController<Asteroid>::Update( Asteroid& model, float dt ) noexcept
	{
		const auto radius = std::visit( [ & ]( auto& astro )
		{
			using type = std::decay_t<decltype( astro )>;
			return type::radius;
		}, model.variant );

		const auto is_leaving =
			( model.position.y + radius < 0.f && model.direction.y < 0.f ) ||
			( model.position.y - radius > screenRect.bottom && model.direction.y > 0.f ) ||
			( model.position.x + radius < 0.f && model.direction.x < 0.f ) ||
			( model.position.x - radius > screenRect.right && model.direction.y > 0.f );

		if( is_leaving )
		{
			model.health = 0.f;
			model.reason = Asteroid::DeathReason::LeftScreen;
		}
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
			return RectF{ -type::radius, -type::radius, type::radius, type::radius } + model.position;
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
