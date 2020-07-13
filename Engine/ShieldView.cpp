#include "ShieldView.h"
#include "Shield.h"
#include <algorithm>

Surface make_shield_sprite()
{
	constexpr auto radius = int( Shield::radius );
	
	auto sprite = Surface( radius * 2, radius * 2 );
	constexpr auto sqrRadius = sqr( Shield::radius );

	for( int y = -radius; y < radius; ++y )
	{
		for( int x = -radius; x < radius; ++x )
		{
			const auto sqrDist = sqr( x ) + sqr( y );
			
			const auto alpha = sqrDist < sqrRadius ? 
				uint8_t( ( sqrDist * 255 ) / sqrRadius ) : 0;

			const auto color = ( sqrDist < sqrRadius ) ?
				Color( Colors::White, alpha ) : Colors::Magenta;

			sprite.PutPixel( x + radius, y + radius, color );
		}
	}

	return sprite;
}


	//const Surface ShieldView::sprite = make_shield_sprite();
	void ShieldView::Draw( Vec2 const& position, Shield const& model, Graphics & gfx ) const noexcept
	{
		const auto t = uint32_t( 255.f * model.health / Shield::recharge_max );
		const auto r = uint8_t( 255u - t );
		const auto g = uint8_t( t );
		const auto b = uint8_t( 0u );
		
		gfx.DrawCircle( position.x, position.y,20,Color( r, g, b ) );
	}
	/*void ShieldView::Draw( Vec2 const& position, Shield const& model, Graphics & gfx ) const noexcept
	{
		const auto t = uint32_t( 255.f * model.health / Shield::recharge_max );
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
	}*/

