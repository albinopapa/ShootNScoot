#pragma once

#include "Vec2.h"

class Vec2Controller
{
public:
	template<typename T>
	static constexpr float Cross( Vec2_<T> const& model, const Vec2_<T>& rhs )noexcept {
		return ( model.x * rhs.y ) - ( model.y * rhs.x );
	}
	template<typename T>
	static constexpr Vec2_<T> Cross( Vec2_<T> const& model, T rhs )noexcept {
		return { model.y * -rhs, model.x * rhs };
	}
	template<typename T>
	static constexpr T Dot( Vec2_<T> const& model, const Vec2_<T>& rhs )noexcept {
		return ( model.x * rhs.x ) + ( model.y * rhs.y );
	}
	template<typename T>
	static constexpr T LengthSq( Vec2_<T> const& model )noexcept
	{
		return Dot( model, model );
	}
	template<typename T>
	static T Length( Vec2_<T> const& model )noexcept
	{
		return ( T )std::sqrt( LengthSq( model ) );
	}
	template<typename T>
	static Vec2_<T> Normalize( Vec2_<T> const& model )noexcept
	{
		const T lenSq = LengthSq( model );
		if( lenSq == T( 0 ) )
		{
			return model;
		}
		else
		{
			const auto len = std::sqrt( lenSq );
			return { model.x / len, model.y / len };
		}
	}

};