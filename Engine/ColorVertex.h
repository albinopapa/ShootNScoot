#pragma once

#include "Colors.h"
#include "Vec2.h"

struct ColorVertex
{
	constexpr ColorVertex operator+( ColorVertex const& rhs )const noexcept
	{
		const auto newColor = Color{
			uint8_t( color.GetA() + rhs.color.GetA() ),
			uint8_t( color.GetR() + rhs.color.GetR() ),
			uint8_t( color.GetG() + rhs.color.GetG() ),
			uint8_t( color.GetB() + rhs.color.GetB() )
		};
		const auto newPosition = position + rhs.position;
		return { newPosition, newColor };
	}
	constexpr ColorVertex operator-( ColorVertex const& rhs )const noexcept
	{
		return{ position - rhs.position, Color{
			uint8_t( color.GetA() - rhs.color.GetA() ),
			uint8_t( color.GetR() - rhs.color.GetR() ),
			uint8_t( color.GetG() - rhs.color.GetG() ),
			uint8_t( color.GetB() - rhs.color.GetB() )
		} };
	}
	constexpr ColorVertex operator*( float rhs )const noexcept
	{
		return{ position * rhs, Color{
			uint8_t( float( color.GetA() ) * rhs ),
			uint8_t( float( color.GetR() ) * rhs ),
			uint8_t( float( color.GetG() ) * rhs ),
			uint8_t( float( color.GetB() ) * rhs )
		} };
	}
	friend constexpr ColorVertex operator*( float lhs, ColorVertex const& rhs )noexcept
	{
		return{ lhs * rhs.position, Color{
			uint8_t( lhs * float( rhs.color.GetA() ) ),
			uint8_t( lhs * float( rhs.color.GetR() ) ),
			uint8_t( lhs * float( rhs.color.GetG() ) ),
			uint8_t( lhs * float( rhs.color.GetB() ) )
		} };
	}

	Vec2 position;
	Color color;
};