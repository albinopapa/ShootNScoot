/******************************************************************************************
*	Chili DirectX Framework Version 16.07.20											  *
*	Colors.h																			  *
*	Copyright 2016 PlanetChili <http://www.planetchili.net>								  *
*																						  *
*	This file is part of The Chili DirectX Framework.									  *
*																						  *
*	The Chili DirectX Framework is free software: you can redistribute it and/or modify	  *
*	it under the terms of the GNU General Public License as published by				  *
*	the Free Software Foundation, either version 3 of the License, or					  *
*	(at your option) any later version.													  *
*																						  *
*	The Chili DirectX Framework is distributed in the hope that it will be useful,		  *
*	but WITHOUT ANY WARRANTY; without even the implied warranty of						  *
*	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the						  *
*	GNU General Public License for more details.										  *
*																						  *
*	You should have received a copy of the GNU General Public License					  *
*	along with The Chili DirectX Framework.  If not, see <http://www.gnu.org/licenses/>.  *
******************************************************************************************/
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
	bool operator==( const Color& rhs ) const noexcept
	{
		return dword == rhs.dword;
	}
	bool operator!=( const Color& rhs ) const noexcept
	{
		return !( *this == rhs );
	}
	constexpr uint8_t GetA() const noexcept
	{
		return dword >> 24u;
	}
	constexpr uint8_t GetR() const noexcept
	{
		return ( dword >> 16u ) & 0xFFu;
	}
	constexpr uint8_t GetG() const noexcept
	{
		return ( dword >> 8u ) & 0xFFu;
	}
	constexpr uint8_t GetB() const noexcept
	{
		return dword & 0xFFu;
	}
	void SetA( uint8_t a )noexcept
	{
		dword = ( dword & 0xFFFFFFu ) | ( a << 24u );
	}
	void SetR( uint8_t r )noexcept
	{
		dword = ( dword & 0xFF00FFFFu ) | ( r << 16u );
	}
	void SetG( uint8_t g )noexcept
	{
		dword = ( dword & 0xFFFF00FFu ) | ( g << 8u );
	}
	void SetB( uint8_t b )noexcept
	{
		dword = ( dword & 0xFFFFFF00u ) | b;
	}

public:
	uint32_t dword;
};

constexpr Color AlphaBlend( Color lhs, Color rhs )noexcept
{
	if( lhs.GetA() == 255 )
		return lhs;
	else if( lhs.GetA() == 0 )
		return rhs;

	const auto sa1 = lhs.GetA();
	const auto sr1 = lhs.GetR();
	const auto sg1 = lhs.GetG();
	const auto sb1 = lhs.GetB();

	const auto sa2 = 255 - sa1;
	const auto sr2 = rhs.GetR();
	const auto sg2 = rhs.GetG();
	const auto sb2 = rhs.GetB();

	const auto r = uint8_t( ( ( sr1 * sa1 ) + ( sr2 * sa2 ) ) >> 8 );
	const auto g = uint8_t( ( ( sg1 * sa1 ) + ( sg2 * sa2 ) ) >> 8 );
	const auto b = uint8_t( ( ( sb1 * sa1 ) + ( sb2 * sa2 ) ) >> 8 );
	const auto a = uint8_t( 255 );

	return{ a, r, g, b };
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