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

		constexpr auto Interpolate( Triangle const& triangle )const noexcept
		{
			return ( triangle.v0 * u ) + ( triangle.v1 * v ) + ( triangle.v2 * w );
		}

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
		auto get_area = [this]( Vec2 const& vpos0, Vec2 const& vpos1, Vec2 const& p ) {
			return ( vpos0 - p ).Cross( vpos1 - p ) * area;
		};

		const auto a = get_area( v1.position, v2.position, p );
		if( a < 0.f || a > 1.f )return {};

		const auto b = get_area( v2.position, v0.position, p );
		if( b < 0.f || b > 1.f )return {};

		const auto c = get_area( v0.position, v1.position, p );
		if( c < 0.f || c > 1.f )return {};

		return std::optional<Barycentric>{ std::in_place_t{}, a, b, c };
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

