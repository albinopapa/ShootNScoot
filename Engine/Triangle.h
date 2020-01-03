#pragma once

#include "Vec2.h"
#include <optional>

template<typename VertexType>
struct Triangle
{
	struct Barycentric
	{
		constexpr Barycentric( float u_, float v_, float w_ )noexcept
			:
			u( u_ ), v( v_ ), w( w_ )
		{}

		float u = -1.f;
		float v = -1.f;
		float w = -1.f;
	};

	constexpr Triangle( VertexType const& v0_, VertexType const& v1_, VertexType const& v2_ )noexcept
		:
		v0( v0_ ),
		v1( v1_ ),
		v2( v2_ ),
		area( 1.f / ( v1.position - v0.position ).Cross( v2.position - v0.position ) )
	{}

	constexpr std::optional<Barycentric> Contains( Vec2 const& p )const noexcept
	{
		const auto a = ( v1.position - p ).Cross( v2.position - p ) * area;
		const auto b = ( v2.position - p ).Cross( v0.position - p ) * area;
		const auto c = ( v0.position - p ).Cross( v1.position - p ) * area;

		const auto contains =
			( a >= 0.f ) & ( a <= 1.f ) &
			( b >= 0.f ) & ( b <= 1.f ) &
			( c >= 0.f ) & ( c <= 1.f );

		return contains != 0 ? 
			std::optional<Barycentric>{std::in_place_t{}, a, b, c} : std::optional<Barycentric>{};
	}
	constexpr auto Interpolate( Barycentric const& coords )const noexcept
	{
		return ( v0 * coords.u ) + ( v1 * coords.v ) + ( v2 * coords.w );
	}
	VertexType v0;
	VertexType v1;
	VertexType v2;

	float area = 0.f;
};

