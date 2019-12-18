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
	constexpr Vec2_ operator+( const Vec2_& rhs ) const noexcept
	{
		return Vec2_( x + rhs.x,y + rhs.y );
	}
	constexpr Vec2_& operator+=( const Vec2_& rhs )noexcept
	{
		return *this = *this + rhs;
	}
	constexpr Vec2_ operator*( T rhs ) const noexcept
	{
		return Vec2_( x * rhs,y * rhs );
	}
	constexpr Vec2_& operator*=( T rhs )noexcept
	{
		return *this = *this * rhs;
	}
	constexpr Vec2_ operator-( const Vec2_& rhs ) const noexcept
	{
		return Vec2_( x - rhs.x,y - rhs.y );
	}
	constexpr Vec2_& operator-=( const Vec2_& rhs )noexcept
	{
		return *this = *this - rhs;
	}
	constexpr float Cross( const Vec2_& rhs )const noexcept {
		return ( x * rhs.y ) - ( y*rhs.x );
	}
	constexpr Vec2_ Cross( T rhs )const noexcept {
		return { y * -rhs, x * rhs };
	}
	constexpr T Dot( const Vec2_& rhs )const noexcept {
		return ( x * rhs.x ) + ( y * rhs.y );
	}
	constexpr T LengthSq() const noexcept
	{
		return Dot( *this );
	}
	T Length() const noexcept
	{
		return (T)std::sqrt( GetLengthSq() );
	}

	Vec2_ Normalize() const noexcept
	{
		const T lenSq = LengthSq();
		if( lenSq == T( 0 ) )
		{
			return *this;
		}
		else
		{
			const auto len = std::sqrt( lenSq );
			return { x / len, y / len };
		}
	}
public:
	T x;
	T y;
};

typedef Vec2_<float> Vec2;
typedef Vec2_<int> Vei2;
