#pragma once

#include "Vec2.h"
#include <array>
#include <optional>

template<typename Vertex>
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

	constexpr Triangle( Vertex const& v0_, Vertex const& v1_, Vertex const& v2_ )noexcept
		:
		v{ v0_, v1_ ,v2_ },
		area( 1.f / ( v1_.position - v0_.position ).Cross( v2_.position - v0_.position ) )
	{}

	constexpr std::optional<Barycentric> Contains( Vec2 const& p )const noexcept
	{
		const auto a = ( v[ 1 ].position - p ).Cross( v[ 2 ].position - p ) * area;
		const auto b = ( v[ 2 ].position - p ).Cross( v[ 0 ].position - p ) * area;
		const auto c = ( v[ 0 ].position - p ).Cross( v[ 1 ].position - p ) * area;

		const auto contains =
			( a >= 0.f ) & ( a <= 1.f ) &
			( b >= 0.f ) & ( b <= 1.f ) &
			( c >= 0.f ) & ( c <= 1.f );

		return contains != 0 ? 
			std::optional<Barycentric>{std::in_place_t{}, a, b, c} : std::optional<Barycentric>{};
	}
	constexpr auto Interpolate( Barycentric const& coords )const noexcept
	{
		return ( v[ 0 ] * coords.u ) + ( v[ 1 ] * coords.v ) + ( v[ 2 ] * coords.w );
	}

	std::array<Vertex, 3> v;
	float area = 0.f;
};

