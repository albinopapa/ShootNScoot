#pragma once

#include <cinttypes>

class Color
{
public:
	Color() = default;
	constexpr Color( uint32_t dw )noexcept
		:
		dword( dw )
	{}
	constexpr Color( uint8_t a, uint8_t r, uint8_t g, uint8_t b )noexcept
		:
		dword( ( a << 24u ) | ( r << 16u ) | ( g << 8u ) | b )
	{}
	constexpr Color( uint8_t r, uint8_t g, uint8_t b )noexcept
		:
		dword( ( 255u << 24u ) | ( r << 16u ) | ( g << 8u ) | b )
	{}
	constexpr Color( Color col, uint8_t a )noexcept
		:
		Color( ( a << 24u ) | ( col.dword & 0x00FFFFFF ) )
	{}

public:
	uint32_t dword;
};


constexpr bool operator==( const Color& lhs, const Color& rhs )noexcept
{
	return lhs.dword == rhs.dword;
}
constexpr bool operator!=( const Color& lhs, const Color& rhs )noexcept
{
	return !( lhs == rhs );
}

namespace Colors
{
	constexpr Color White		= Color( 255u, 255u, 255u );
	constexpr Color Black		= Color( 0u, 0u, 0u );
	constexpr Color Gray		= Color( 0x80u, 0x80u, 0x80u );
	constexpr Color LightGray	= Color( 0xD3u, 0xD3u, 0xD3u );
	constexpr Color Red			= Color( 255u, 0u, 0u );
	constexpr Color Green		= Color( 0u, 255u, 0u );
	constexpr Color Blue		= Color( 0u, 0u, 255u );
	constexpr Color Yellow		= Color( 255u, 255u, 0u );
	constexpr Color Cyan		= Color( 0u, 255u, 255u );
	constexpr Color Magenta		= Color( 255u, 0u, 255u );
}