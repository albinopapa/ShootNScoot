#include "Asteroids.h"
#include "ChiliMath.h"
#include <algorithm>

void sns::Asteroid::Update( float dt ) noexcept
{
	std::visit( [ & ]( const auto& astro ) {
		using type = std::decay_t<decltype( astro )>;

		position += ( direction * ( dt * Asteroid::speed ) );
		const auto is_leaving =
			( position.y + type::radius < 0.f && direction.y < 0.f ) ||
			( position.y - type::radius > screenRect.bottom && direction.y > 0.f ) ||
			( position.x + type::radius < 0.f && direction.x < 0.f ) ||
			( position.x - type::radius > screenRect.right && direction.y > 0.f );
		
		if(is_leaving)
		{
			health = 0.f;
			reason = DeathReason::LeftScreen;
		}
	}, variant );
}

void sns::Asteroid::TakeDamage( float amount ) noexcept
{
	health -= amount;
}

void sns::Asteroid::Draw( Graphics & gfx ) const noexcept
{
	std::visit( [ & ]( auto const& astro )
	{
		using type = std::decay_t<decltype( astro )>;

		const auto astro_aabb = AABB();

		const auto xStart = int( std::max( 0.f, -astro_aabb.left ) - type::radius );
		const auto yStart = int( std::max( 0.f, -astro_aabb.top ) - type::radius );
		const auto xEnd = int( std::min( screenRect.Width() - astro_aabb.left, astro_aabb.Width() ) - type::radius );
		const auto yEnd = int( std::min( screenRect.Height() - astro_aabb.top, astro_aabb.Height() ) - type::radius );

		constexpr auto sqrRadius = int( sqr( type::radius ) );
		const auto iPos = Vei2{ int( position.x ), int( position.y ) };

		for( auto y = yStart; y < yEnd; ++y )
		{
			for( auto x = xStart; x < xEnd; ++x )
			{
				if( sqr( x ) + sqr( y ) < sqrRadius )
				{
					gfx.PutPixel( x + iPos.x, y + iPos.y, Asteroid::color );
				}
			}
		}
	}, variant );
}

RectF sns::Asteroid::AABB() const noexcept
{
	return std::visit( [ & ]( auto const& astro ) {
		using type = std::decay_t<decltype( astro )>;
		return RectF{ -type::radius, -type::radius, type::radius, type::radius } + position;
	}, variant );
}

float sns::Asteroid::Damage() const noexcept
{
	return std::visit( [ & ]( auto const& astro ) {
		using type = std::decay_t<decltype( astro )>;
		return type::damage;
	}, variant );
}

int sns::Asteroid::ScoreValue() const noexcept
{
	return std::visit( [ & ]( auto const& astro ) {
		using type = std::decay_t<decltype( astro )>;
		return type::score_value;
	}, variant );
}
