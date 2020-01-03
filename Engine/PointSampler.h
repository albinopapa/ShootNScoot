#pragma once

#include "Colors.h"
#include "Surface.h"
#include "Vec2.h"

struct PointSampler
{
	Color operator()( Surface const& sprite, Vec2 const& texcoord )const noexcept
	{
		return sprite.GetPixel(
			int( texcoord.x * float( sprite.GetWidth() - 1 ) ),
			int( texcoord.y * float( sprite.GetHeight() - 1 ) )
		);
	}

};