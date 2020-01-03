#include "ShieldView.h"
#include "Shield.h"
#include <algorithm>

Surface make_shield_sprite()
{
	auto sprite = Surface( int( sns::Shield::radius * 2.f ), int( sns::Shield::radius * 2.f ) );
	constexpr auto sqrRadius = sqr( sns::Shield::radius );

	for( int y = -int( sns::Shield::radius ); y < int( sns::Shield::radius ); ++y )
	{
		for( int x = -int( sns::Shield::radius ); x < int( sns::Shield::radius ); ++x )
		{
			const auto sqrDist = sqr( x ) + sqr( y );
			
			const auto alpha = sqrDist < sqrRadius ? uint8_t( ( sqrDist * 255 ) / sqrRadius ) : 0;

			const auto color = ( sqrDist < sqrRadius ) ?
				Color( Colors::White, alpha ) : Colors::Magenta;

			sprite.PutPixel(
				x + int( sns::Shield::radius ),
				y + int( sns::Shield::radius ),
				color
			);
		}
	}

	return sprite;
}

namespace sns
{
	const Surface ShieldView::sprite = make_shield_sprite();

	void ShieldView::Draw( Vec2 const& position, Shield const& model, Graphics & gfx ) const noexcept
	{
		const auto t = uint32_t( 255.f * model.health / Shield::health_min );
		const auto r = uint8_t( 255u - t );
		const auto g = uint8_t( t );
		const auto b = uint8_t( 0u );
		constexpr auto rect = RectF{
			-Shield::radius,
			-Shield::radius,
			Shield::radius,
			Shield::radius
		};
		gfx.DrawSprite( rect + position, Radian{ 0.f }, sprite, Color( r, g, b ) );
	}
}
