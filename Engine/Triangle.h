#pragma once

#include "Vec2.h"
#include "Vec2Controller.h"
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
		area( 1.f / Vec2Controller::Cross( v1_.position - v0_.position, v2_.position - v0_.position ) )
	{}

	constexpr std::optional<Barycentric> Contains( Vec2 const& p )const noexcept
	{
		const auto a = Vec2Controller::Cross( v[ 1 ].position - p, v[ 2 ].position - p ) * area;
		if( ( a < 0.f ) && ( a > 1.f ) )return std::optional<Barycentric>{};

		const auto b = Vec2Controller::Cross( v[ 2 ].position - p, v[ 0 ].position - p ) * area;
		if( ( b < 0.f ) && ( b > 1.f ) )return std::optional<Barycentric>{};

		//const auto c = ( v[ 0 ].position - p ).Cross( v[ 1 ].position - p ) * area;
		//if( ( c < 0.f ) && ( c > 1.f ) )return std::optional<Barycentric>{};
		const auto c = 1.f - a - b;
		return std::optional<Barycentric>{std::in_place_t{}, a, b, c};
	}
	constexpr auto Interpolate( Barycentric const& coords )const noexcept
	{
		return ( v[ 0 ] * coords.u ) + ( v[ 1 ] * coords.v ) + ( v[ 2 ] * coords.w );
	}

	std::array<Vertex, 3> v;
	float area = 0.f;
};

