#pragma once

#include "Rect.h"

class RectController
{
public:
	template<typename T>
	static constexpr auto FromCenter( const Vec2_<T>& center, const Size<T>& halfSize )noexcept
	{
		const auto half = Vec2_<T>( halfSize.width, halfSize.height );
		return Rect_<T>( center - half, center + half );
	}

	template<typename T>
	static constexpr auto Overlaps( Rect<T> const& model, const Rect<T>& rhs )noexcept
	{
		return model.right > rhs.left && model.left < rhs.right
			&& model.bottom > rhs.top && model.top < rhs.bottom;
	}
	template<typename T>
	static constexpr auto IsContainedBy( Rect<T> const& model, const Rect<T>& rhs )noexcept
	{
		return 
			model.left >= rhs.left && model.right <= rhs.right &&
			model.top >= rhs.top && model.bottom <=  rhs.bottom;
	}
	template<typename T>
	static constexpr auto Contains( Rect<T> const& model, const Vec2_<T>& point )noexcept
	{
		return 
			point.x >= model.left && point.x < model.right && 
			point.y >= model.top && point.y < model.bottom;
	}
	template<typename T>
	static constexpr auto Expand( Rect<T> const& model, T offset )noexcept
	{
		return Rect<T>{
			model.left - offset,
			model.top - offset,
			model.right + offset,
			model.bottom + offset
		}
	}
	template<typename T>
	static constexpr auto Center( Rect<T> const& model )noexcept
	{
		return Vec2_<T>{
			model.left + Width( model ) / ( T )2,
			model.top + Height( model ) / ( T )2
		};
	}
	template<typename T>
	static constexpr auto Width( Rect<T> const& model )noexcept
	{
		return model.right - model.left;
	}
	template<typename T>
	static constexpr auto Height( Rect<T> const& model )noexcept
	{
		return model.bottom - model.top;
	}

};