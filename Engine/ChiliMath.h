#pragma once

#include <cmath>

template<typename T> 
constexpr T sqr( const T& value )noexcept 
{
	return value * value;
}

template<typename T> 
constexpr T lerp( T const& start, T const& end, float t )noexcept 
{
	return start + ( ( end - start ) * t );
}