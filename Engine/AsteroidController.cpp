#include "AsteroidController.h"
#include "Graphics.h"

void AsteroidController::Update( Asteroid& model, float dt ) noexcept
{
	std::visit( [&]( auto& astro )
	{
		using type = std::decay_t<decltype( astro )>;
		constexpr auto size = SizeF{ type::radius, type::radius };
		
		if( !Graphics::IsVisible( RectF::FromCenter( model.position, size ) ) &&
			( Graphics::GetRect<float>().Center() - model.position ).Dot( model.direction ) <= 0.f )
		{
			model.health = 0.f;
			model.reason = AsteroidDeathReason::LeftScreen;
		}
	}, model.variant );
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
		return RectF::FromCenter( model.position, SizeF{ type::radius, type::radius } );
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
