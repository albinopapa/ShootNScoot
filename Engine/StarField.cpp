#include "StarField.h"

sns::StarField::StarField()
{
	for( auto& star : stars )
	{
		star.position = Vec2{ xDist( rng ), yDist( rng ) };
		star.speed = spdDist( rng );
	}
}

void sns::StarField::Update() noexcept
{
	for( auto& star : stars )
	{
		star.position += { 0.f, star.speed };
		if( !screenRect.Contains( star.position ) )
		{
			star.position = { xDist( rng ), 0.f };
			star.speed = spdDist( rng );
		}
	}
}

void sns::StarField::Draw( Graphics & gfx ) const noexcept
{
	for( auto const& star : stars )
	{
		constexpr int radius = 1;
		for( int y = -radius; y < radius; ++y )
		{
			for( int x = -radius; x < radius; ++x )
			{
				gfx.PutPixelClipped( int( star.position.x ) + x, int( star.position.y ) + y, Colors::White );
			}
		}
	}
}
