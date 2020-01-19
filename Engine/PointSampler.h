#pragma once

#include "Colors.h"
#include "Surface.h"
#include "SurfaceController.h"
#include "Vec2.h"

struct PointSampler
{
	Color operator()( Surface const& sprite, Vec2 const& texcoord )const noexcept
	{
		const auto tc = WrapTexcoord( texcoord );
		const auto texel = CalculateCoord( sprite, tc );
		return SurfaceController::GetPixel( sprite, texel );
	}

private:
	static constexpr Vec2 WrapTexcoord( Vec2 texcood )noexcept
	{
		while( texcood.x < 0.f )texcood.x += 1.f;
		while( texcood.x > 1.f )texcood.x -= 1.f;
		while( texcood.y < 0.f )texcood.y += 1.f;
		while( texcood.y > 1.f )texcood.y -= 1.f;
		return texcood;
	}
	static Point CalculateCoord( Surface const& sprite, Vec2 const& texcoord )noexcept
	{
		const auto width = float( SurfaceController::GetWidth( sprite ) - 1 );
		const auto height = float( SurfaceController::GetHeight( sprite ) - 1 );

		return { int( texcoord.x * width ), int( texcoord.y * height ) };
	}
};