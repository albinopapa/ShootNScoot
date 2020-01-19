#pragma once

#include "Colors.h"

struct ColorController
{
	static constexpr uint8_t GetA( Color const& model ) noexcept
	{
		return model.dword >> 24u;
	}
	static constexpr uint8_t GetR( Color const& model ) noexcept
	{
		return ( model.dword >> 16u ) & 0xFFu;
	}
	static constexpr uint8_t GetG( Color const& model ) noexcept
	{
		return ( model.dword >> 8u ) & 0xFFu;
	}
	static constexpr uint8_t GetB( Color const& model ) noexcept
	{
		return model.dword & 0xFFu;
	}
	static constexpr void SetA( Color& model, uint8_t a )noexcept
	{
		model.dword = ( model.dword & 0xFFFFFFu ) | ( a << 24u );
	}
	static constexpr void SetR( Color& model, uint8_t r )noexcept
	{
		model.dword = ( model.dword & 0xFF00FFFFu ) | ( r << 16u );
	}
	static constexpr void SetG( Color& model, uint8_t g )noexcept
	{
		model.dword = ( model.dword & 0xFFFF00FFu ) | ( g << 8u );
	}
	static constexpr void SetB( Color& model, uint8_t b )noexcept
	{
		model.dword = ( model.dword & 0xFFFFFF00u ) | b;
	}

	static constexpr Color AlphaBlend( Color lhs, Color rhs )noexcept
	{
		if( GetA( lhs ) == 255 ) return lhs;
		else if( GetA( lhs ) == 0 ) return rhs;

		const auto sa1 = GetA( lhs );
		const auto sr1 = GetR( lhs );
		const auto sg1 = GetG( lhs );
		const auto sb1 = GetB( lhs );

		const auto sa2 = 255 - sa1;
		const auto sr2 = GetR( rhs );
		const auto sg2 = GetG( rhs );
		const auto sb2 = GetB( rhs );

		return{
			uint8_t( ( ( sr1 * sa1 ) + ( sr2 * sa2 ) ) >> 8 ),
			uint8_t( ( ( sg1 * sa1 ) + ( sg2 * sa2 ) ) >> 8 ),
			uint8_t( ( ( sb1 * sa1 ) + ( sb2 * sa2 ) ) >> 8 )
		};
	}

};