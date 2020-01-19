#pragma once

#include "Colors.h"
#include "ColorController.h"
#include "Vec2.h"

struct ColorVertex
{
	constexpr ColorVertex operator+( ColorVertex const& rhs )const noexcept
	{
		const auto newColor = Color{
			uint8_t( ColorController::GetA( color ) + ColorController::GetA( rhs.color ) ),
			uint8_t( ColorController::GetR( color ) + ColorController::GetR( rhs.color ) ),
			uint8_t( ColorController::GetG( color ) + ColorController::GetG( rhs.color ) ),
			uint8_t( ColorController::GetB( color ) + ColorController::GetB( rhs.color ) )
		};
		const auto newPosition = position + rhs.position;
		return { newPosition, newColor };
	}
	constexpr ColorVertex operator-( ColorVertex const& rhs )const noexcept
	{
		return{ position - rhs.position, Color{
			uint8_t( ColorController::GetA( color ) - ColorController::GetA( rhs.color ) ),
			uint8_t( ColorController::GetR( color ) - ColorController::GetR( rhs.color ) ),
			uint8_t( ColorController::GetG( color ) - ColorController::GetG( rhs.color ) ),
			uint8_t( ColorController::GetB( color ) - ColorController::GetB( rhs.color ) )
		} };
	}
	constexpr ColorVertex operator*( float rhs )const noexcept
	{
		return{ position * rhs, Color{
			uint8_t( float( ColorController::GetA( color ) ) * rhs ),
			uint8_t( float( ColorController::GetR( color ) ) * rhs ),
			uint8_t( float( ColorController::GetG( color ) ) * rhs ),
			uint8_t( float( ColorController::GetB( color ) ) * rhs )
		} };
	}
	friend constexpr ColorVertex operator*( float lhs, ColorVertex const& rhs )noexcept
	{
		return{ lhs * rhs.position, Color{
			uint8_t( lhs * float( ColorController::GetA( rhs.color ) ) ),
			uint8_t( lhs * float( ColorController::GetR( rhs.color ) ) ),
			uint8_t( lhs * float( ColorController::GetG( rhs.color ) ) ),
			uint8_t( lhs * float( ColorController::GetB( rhs.color ) ) )
		} };
	}

	Vec2 position;
	Color color;
};