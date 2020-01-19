#pragma once

#include "Rect.h"
#include "Size.h"
#include "Vec2.h"

namespace sns
{
	constexpr auto cell_size  = 128;
	constexpr auto grid_size  = SizeI{ 16, 9 };
	constexpr auto world_size = SizeF{ float( grid_size.width * cell_size ), float( grid_size.height * cell_size ) };
	constexpr auto world_rect = RectF{ Vec2{0.f, 0.f}, world_size } + ( -Vec2( world_size.width * .5f, world_size.height * .5f ) );
	constexpr auto viewport_size = SizeF{ 800.f, 600.f };
	constexpr auto screen_rect = RectF{ Vec2{-viewport_size.width * .5f, -viewport_size.height * .5f}, viewport_size };
}