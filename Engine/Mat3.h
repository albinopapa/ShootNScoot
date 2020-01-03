#pragma once

#include "AngleMath.h"
#include "Vec2.h"
#include <cmath>

struct Vec3
{
	float x = 0.f;
	float y = 0.f;
	float z = 1.f;
};

template<typename T>
struct Mat3
{
	using Vector = Vec2_<T>;

	static constexpr Mat3 Translation( Vector const& position )noexcept
	{
		return{
			Vector{ 1.f, 0.f },
			Vector{ 0.f, 1.f },
			position
		};
	}
	static constexpr Mat3 Scale( float xScale, float yScale )noexcept
	{
		return {
			Vector{ xScale,    0.f },
			Vector{	   0.f, yScale },
			Vector{	   0.f,    0.f }
		};
	}
	static Mat3 Rotate( Radian angle )noexcept
	{
		const auto c = Cos( angle );
		const auto s = Sin( angle );

		return {
			Vector{ c, -s },
			Vector{ s,  c },
			Vector{ T( 0 ), T( 0 ) }
		};
	}

	constexpr Vec2_<T> operator*( const Vec2_<T>& rhs )const noexcept
	{
		return { 
			row[ 0 ].x * rhs.x + row[ 1 ].x * rhs.y + row[ 2 ].x,
			row[ 0 ].y * rhs.x + row[ 1 ].y * rhs.y + row[ 2 ].y 
		};
	}
	constexpr Mat3 operator*( const Mat3& rhs )const noexcept
	{
		const auto r0 = Vector{
			row[ 0 ].x * rhs.row[ 0 ].x + row[ 0 ].y * rhs.row[ 1 ].x,
			row[ 0 ].x * rhs.row[ 0 ].y + row[ 0 ].y * rhs.row[ 1 ].y
		};
		const auto r1 = Vector{
			row[ 1 ].x * rhs.row[ 0 ].x + row[ 1 ].y * rhs.row[ 1 ].x,
			row[ 1 ].x * rhs.row[ 0 ].y + row[ 1 ].y * rhs.row[ 1 ].y
		};
		const auto r2 = Vector{
			row[ 2 ].x * rhs.row[ 0 ].x + row[ 2 ].y * rhs.row[ 1 ].x + rhs.row[ 2 ].x,
			row[ 2 ].y * rhs.row[ 0 ].y + row[ 2 ].y * rhs.row[ 1 ].y + rhs.row[ 2 ].y
		};

		return { r0, r1, r2 };
	}
	Vector row[ 3 ];
};

using Mat3F = Mat3<float>;