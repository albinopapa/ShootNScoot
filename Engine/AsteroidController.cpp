#include "AsteroidController.h"
#include "Asteroids.h"
#include "Graphics.h"

namespace sns
{
	void AsteroidController::Update( Asteroid& model, float dt ) noexcept
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
			model.reason = AsteroidDeathReason::LeftScreen;
		}
	}

	void AsteroidController::TakeDamage( Asteroid& model, float amount ) noexcept
	{
		model.health -= amount;
	}

	void AsteroidController::Reason( Asteroid& model, AsteroidDeathReason reason ) noexcept
	{
		model.reason = reason;
	}

	RectF AsteroidController::AABB( Asteroid const& model )noexcept
	{
		return std::visit( [ & ]( auto const& astro ) {
			using type = std::decay_t<decltype( astro )>;
			return RectF{ -type::radius, -type::radius, type::radius, type::radius } + model.position;
		}, model.variant );
	}

	float AsteroidController::Damage( Asteroid const& model )noexcept
	{
		return std::visit( [ & ]( auto const& astro ) {
			using type = std::decay_t<decltype( astro )>;
			return type::damage;
		}, model.variant );
	}

	float AsteroidController::Health( Asteroid const& model )noexcept
	{
		return model.health;
	}

	AsteroidDeathReason AsteroidController::Reason( Asteroid const& model )noexcept
	{
		return model.reason;
	}

	int AsteroidController::ScoreValue( Asteroid const& model )noexcept
	{
		return std::visit( [ & ]( auto const& astro ) {
			using type = std::decay_t<decltype( astro )>;
			return type::score_value;
		}, model.variant );
	}
}
