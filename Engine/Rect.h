#pragma once

#include "Vec2.h"
#include "Size.h"

template<typename T>
class Rect_
{
public:
	Rect_() = default;
		
	constexpr Rect_( T left_in, T top_in, T right_in, T bottom_in )noexcept
		:
		left( left_in ),
		right( right_in ),
		top( top_in ),
		bottom( bottom_in )
	{}
	constexpr Rect_( const Vec2_<T>& topLeft, const Vec2_<T>& bottomRight )noexcept
		:
		Rect_( topLeft.x, topLeft.y, bottomRight.x, bottomRight.y )
	{}
	constexpr Rect_( const Vec2_<T>& topLeft, const Size<T>& size )noexcept
		:
		Rect_( topLeft.x, topLeft.y, topLeft.x + size.width, topLeft.y + size.height )
	{}
	template<typename U>
	constexpr Rect_( const Rect_<U>& rhs )noexcept
		:
		Rect_( T( rhs.left ), T( rhs.top ), T( rhs.right ), T( rhs.bottom ) )
	{}
	constexpr bool Overlaps( const Rect_& other ) const noexcept
	{
		return right > other.left && left < other.right
			&& bottom > other.top && top < other.bottom;
	}
	constexpr bool IsContainedBy( const Rect_& other ) const noexcept
	{
		return left >= other.left && right <= other.right &&
			top >= other.top && bottom <= other.bottom;
	}
	constexpr bool Contains( const Vec2_<T>& point ) const noexcept
	{
		return point.x >= left && point.x < right && point.y >= top && point.y < bottom;
	}
	static constexpr Rect_ FromCenter( const Vec2_<T>& center, const Size<T>& halfSize )noexcept
	{
		return Rect_( center - halfSize, center + halfSize );
	}
	constexpr Rect_ Expand( T offset ) const noexcept
	{
		return Rect_( left - offset, right + offset, top - offset, bottom + offset );
	}
	constexpr Vec2_<T> Center() const noexcept
	{
		return Vec2_<T>( ( left + right ) / ( T )2, ( top + bottom ) / ( T )2 );
	}
	constexpr T Width() const noexcept
	{
		return right - left;
	}
	constexpr T Height() const noexcept
	{
		return bottom - top;
	}
	constexpr Rect_ operator+( Vec2_<T> const& offset )const noexcept {
		return{
			left	+ offset.x,
			top		+ offset.y,
			right	+ offset.x,
			bottom	+ offset.y
		};
	}
	constexpr Rect_ operator-( Vec2_<T> const& offset )const noexcept {
		return{
			left - offset.x,
			top - offset.y,
			right - offset.x,
			bottom - offset.y
		};
	}
public:
	T left = {};
	T top = {};
	T right = {};
	T bottom = {};
};

typedef Rect_<int> RectI;
typedef Rect_<float> RectF;