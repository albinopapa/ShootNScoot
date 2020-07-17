#pragma once

#include "Surface.h"

#include <sstream>
#include <vector>

struct SpriteCache
{
	SpriteCache()
		:
		ship1_frames( make_ship_frames( "Images/Ship1_trans.png" ) ),
		ship2_frames( make_ship_frames( "Images/Ship2_trans.png" ) )
	{
	}

private:
	std::vector<Surface> make_ship_frames( std::string filename ) {
		auto frames = std::vector<Surface>{};
		frames.reserve( 8 );

		auto temp = Surface{ std::move( filename ) };
		const auto width = temp.GetWidth() / 5;
		const auto height = temp.GetHeight();
		for( auto i = std::size_t{}; i < 5; ++i ) {
			auto& frame = frames.emplace_back( width, height );
			const auto xStart = int( i ) * width;
			const auto xEnd = ( int( i ) * width ) + width;

			for( int y = 0; y < height; ++y ) {
				for( int x = xStart, dx = 0; x < xEnd; ++x, ++dx ) {
					frame.PutPixel( dx, y, temp.GetPixel( x, y ) );
				}
			}
		}

		const auto right = width - 1;
		for( auto i = std::size_t{ 1 }; i < 4; ++i ) {
			auto& frame = frames.emplace_back( width, height );
			const auto& src = frames[ i ];

			for( int y = 0; y < height; ++y ) {
				for( int x = 0; x < width; ++x ) {
					frame.PutPixel( right - x, y, src.GetPixel( x, y ) );
				}
			}
		}

		return frames;
	}

public:
	Surface hero_sprite = "Images/Player_Ships_1.png";
	Surface bullet_sprite;
	Surface asteroid_sprite;
	Surface plasmaball_sprite;
	std::vector<Surface> ship1_frames;
	std::vector<Surface> ship2_frames;
};
