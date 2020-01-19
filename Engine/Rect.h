#pragma once

#include "Vec2.h"
#include "Size.h"

template<typename T>
class Rect
{
public:
	Rect() = default;
		
	constexpr Rect( T left_in, T top_in, T right_in, T bottom_in )noexcept
		:
		left( left_in ),
		top( top_in ),
		right( right_in ),
		bottom( bottom_in )
	{}
	constexpr Rect( const Vec2_<T>& topLeft, const Vec2_<T>& bottomRight )noexcept
		:
		Rect( topLeft.x, topLeft.y, bottomRight.x, bottomRight.y )
	{}
	constexpr Rect( const Vec2_<T>& topLeft, const Size<T>& size )noexcept
		:
		Rect( topLeft.x, topLeft.y, topLeft.x + size.width, topLeft.y + size.height )
	{}
	constexpr Rect( Size<T> const& size )noexcept
		:
		Rect( T( 0 ), T( 0 ), size.width, size.height )
	{}
	template<typename U>
	constexpr Rect( const Rect<U>& rhs )noexcept
		:
		Rect( T( rhs.left ), T( rhs.top ), T( rhs.right ), T( rhs.bottom ) )
	{}
	constexpr Rect operator+( Vec2_<T> const& offset )const noexcept {
		return{
			left	+ offset.x,
			top		+ offset.y,
			right	+ offset.x,
			bottom	+ offset.y
		};
	}
	constexpr Rect operator-( Vec2_<T> const& offset )const noexcept
	{
		return *this + ( -offset );
	}
public:
	T left;
	T top;
	T right;
	T bottom;
};

using RectI = Rect<int>;
using RectF = Rect<float>;

template<typename T>
constexpr Vec2_<T> operator*( Vec2 const& lhs, Size<T> const& rhs )noexcept
{
	return { lhs.x * rhs.width, lhs.y * rhs.height };
}