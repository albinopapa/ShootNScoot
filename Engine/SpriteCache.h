#pragma once

#include "Surface.h"

#include <sstream>
#include <vector>

struct SpriteCache
{
	SpriteCache()
	{
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
		{
			auto sheet = Surface{ "Enemy_Example_1-a.png" };
			enemy1_ship = load_from_sheet( { 130, 164, 173, 216 }, sheet );
			enemy2_ship = load_from_sheet( { 129,  82, 174, 147 }, sheet );
			enemy3_ship = load_from_sheet( { 129,   9, 169,  59 }, sheet );
			enemy4_ship = load_from_sheet( {   8,  52, 113, 178 }, sheet );
		}

	}

private:
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

		return load_from_sheet( rect, sheet );
	}

	Surface load_from_sheet( RectI const& rect, Surface const& sheet ) {
		auto temp = Surface{ rect.Width(), rect.Height() };
		
		for( int sy = rect.top, dy = 0; sy < rect.bottom; ++sy, ++dy ) {
			const auto src_row_offset = sy * sheet.GetWidth();
			const auto dst_row_offset = dy * rect.Width();

			const auto* src = sheet.Data() + ( rect.left + src_row_offset );
			auto* dst = temp.Data() + dst_row_offset;

			memcpy( dst, src, sizeof( Color ) * rect.Width() );
		}

		return temp;
	}
public:
	Surface hero_sprite = "Images/Player_Ships_1-mini.png";
	Surface bullet_sprite;
	std::vector<Surface> asteroid_fames;
	Surface plasmaball_sprite;
	Surface enemy1_ship;
	Surface enemy2_ship;
	Surface enemy3_ship;
	Surface enemy4_ship;

};
