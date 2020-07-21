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
		auto sheet = Surface{ "Images/Alien_EggSplode.png" };
		asteroid_fames.push_back( make_asteroid_frame( 0, sheet ) );
		// Second frame not needed
		asteroid_fames.push_back( make_asteroid_frame( 1, sheet ) );
		asteroid_fames.push_back( make_asteroid_frame( 2, sheet ) );
		asteroid_fames.push_back( make_asteroid_frame( 3, sheet ) );
		asteroid_fames.push_back( make_asteroid_frame( 4, sheet ) );
		asteroid_fames.push_back( make_asteroid_frame( 5, sheet ) );

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
	Surface make_asteroid_frame( int index, Surface const& sheet ) {
		auto rect = RectI{
			std::numeric_limits<int>::max(),
			std::numeric_limits<int>::max(),
			std::numeric_limits<int>::min(),
			std::numeric_limits<int>::min()
		};

		constexpr auto sheet_ramiander = 282 - 142;
		constexpr auto stepping = sheet_ramiander / 5;
		const auto starting_index = index - 1;
		auto [xStart, xEnd] = [&]() {
			if( index == 0 )
				return std::pair{ index * 60, ( index + 1 ) * 60 };
			else
				return std::pair{ 
					142 + ( starting_index * stepping ), 
					142 + ( ( starting_index + 1 ) * stepping ) 
				};
		}( );
		
		for( int y = 0; y < sheet.GetHeight(); ++y ) {
			for( int x = xStart; x < xEnd; ++x ) {
				if( auto color = sheet.GetPixel( x, y ); color.GetA() != 0 ) {
					rect.left = std::min( x, rect.left );
					rect.top = std::min( y, rect.top );
					rect.right = std::max( x, rect.right );
					rect.bottom = std::max( y, rect.bottom );
				}
			}
		}

		auto temp = Surface{ rect.Width(), rect.Height() };
		for( int y = rect.top; y < rect.bottom; ++y ) {
			for( int x = rect.left; x < rect.right; ++x ) {
				const auto dx = x - rect.left;
				const auto dy = y - rect.top;
				temp.PutPixel( dx, dy, sheet.GetPixel( x, y ) );
			}
		}
		return temp;

	}
public:
	Surface hero_sprite = "Images/Player_Ships_1-mini.png";
	Surface bullet_sprite;
	std::vector<Surface> asteroid_fames;
	Surface plasmaball_sprite;
	std::vector<Surface> ship1_frames;
	std::vector<Surface> ship2_frames;
};
