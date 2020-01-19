#include "Shield.h"
#include "ChiliMath.h"
#include "SurfaceController.h"

namespace sns
{
	const Surface Shield::sprite = Shield::MakeSprite();

	Surface Shield::MakeSprite()
	{
		constexpr auto iRadius = int( radius );
		auto sprite = SurfaceController::CreateSurface( iRadius * 2, iRadius * 2 );
		constexpr auto sqrRadius = sqr( iRadius );

		for( int y = -iRadius; y < iRadius; ++y )
		{
			for( int x = -iRadius; x < iRadius; ++x )
			{
				const auto sqrDist = sqr( x ) + sqr( y );

				const auto alpha = sqrDist < sqrRadius ?
					uint8_t( ( sqrDist * 255 ) / sqrRadius ) : 0;

				const auto color = ( sqrDist < sqrRadius ) ?
					Color( Colors::White, alpha ) : Colors::Magenta;

				SurfaceController::PutPixel( sprite, { x + iRadius, y + iRadius }, color );
			}
		}

		return sprite;
	}
}
