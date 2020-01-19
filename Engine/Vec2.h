#pragma once

#include <cmath>

template<typename T>
class Vec2_
{
public:
	Vec2_() = default;
	constexpr Vec2_( T x_in,T y_in )noexcept
		:
		x( x_in ),
		y( y_in )
	{}
	template<typename S> explicit Vec2_( const Vec2_<S>& src )noexcept
		:
		x( (T)src.x ),
		y( (T)src.y )
	{}
	constexpr Vec2_ operator-()const noexcept
	{
		return { -x, -y };
	}
	constexpr Vec2_ operator+( const Vec2_& rhs ) const noexcept
	{
		return Vec2_( x + rhs.x,y + rhs.y );
	}
	constexpr Vec2_ operator-( const Vec2_& rhs ) const noexcept
	{
		return Vec2_( x - rhs.x,y - rhs.y );
	}
	constexpr Vec2_ operator*( T rhs ) const noexcept
	{
		return Vec2_( x * rhs,y * rhs );
	}
	friend constexpr Vec2_ operator*( float lhs, Vec2_ const& rhs )noexcept
	{
		return{ lhs * rhs.x, lhs * rhs.y };
	}
	constexpr Vec2_& operator+=( const Vec2_& rhs )noexcept
	{
		return *this = *this + rhs;
	}
	constexpr Vec2_& operator*=( T rhs )noexcept
	{
		return *this = *this * rhs;
	}
	constexpr Vec2_& operator-=( const Vec2_& rhs )noexcept
	{
		return *this = *this - rhs;
	}
public:
	T x;
	T y;
};

typedef Vec2_<float> Vec2;
typedef Vec2_<int> Vei2;
using Point = Vec2_<int>;