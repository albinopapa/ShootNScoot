#include "AsteroidController.h"
#include "Graphics.h"

void AsteroidController::Update( Asteroid& model, float dt ) noexcept
{
	const auto radius = std::visit( [&]( auto& astro )
	{
		using type = std::decay_t<decltype( astro )>;
		return type::radius;
	}, model.variant );

	const auto is_leaving =
		( model.position.y + radius < 0.f && model.direction.y < 0.f ) ||
		( model.position.y - radius > Graphics::GetRect<float>().bottom && model.direction.y > 0.f ) ||
		( model.position.x + radius < 0.f && model.direction.x < 0.f ) ||
		( model.position.x - radius > Graphics::GetRect<float>().right && model.direction.y > 0.f );

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

RectF AsteroidController::AABB( Asteroid& model ) const noexcept
{
	return std::visit( [&]( auto const& astro ) {
		using type = std::decay_t<decltype( astro )>;
		return RectF{ -type::radius, -type::radius, type::radius, type::radius } + model.position;
	}, model.variant );
}

float AsteroidController::Damage( Asteroid& model ) const noexcept
{
	return std::visit( [&]( auto const& astro ) {
		using type = std::decay_t<decltype( astro )>;
		return type::damage;
	}, model.variant );
}

float AsteroidController::Health( Asteroid& model ) const noexcept
{
	return model.health;
}

AsteroidDeathReason AsteroidController::Reason( Asteroid& model ) const noexcept
{
	return model.reason;
}

int AsteroidController::ScoreValue( Asteroid& model ) const noexcept
{
	return std::visit( [&]( auto const& astro ) {
		using type = std::decay_t<decltype( astro )>;
		return type::score_value;
	}, model.variant );
}
