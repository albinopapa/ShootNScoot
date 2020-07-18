#pragma once

#include "ChiliMath.h"

constexpr auto pi = 3.1415926f;
constexpr auto rad_factor = pi / 180.f;
constexpr auto deg_factor = 180.f / pi;

class Degree;
class Radian;

class Degree
{
public:
	Degree() = default;
	constexpr Degree( Radian )noexcept;
	explicit constexpr Degree( float )noexcept;
	constexpr operator float()const noexcept
	{
		return value;
	}
	constexpr Degree& operator+=( Degree rhs )noexcept
	{
		value += rhs.value;
		return *this;
	}
	constexpr Degree& operator-=( Degree rhs )noexcept
	{
		value -= rhs.value;
		return *this;
	}
	constexpr Degree& operator*=( float rhs )noexcept
	{
		value *= rhs;
		return *this;
	}
	constexpr Degree& operator/=( float rhs )noexcept
	{
		value /= rhs;
		return *this;
	}

	constexpr bool operator==( Degree rhs )const noexcept
	{
		return value == rhs.value;
	}
	constexpr bool operator!=( Degree rhs )const noexcept
	{
		return !( *this == rhs );
	}
	constexpr bool operator<( Degree rhs )const noexcept
	{
		return value < rhs.value;
	}
	constexpr bool operator<=( Degree rhs )const noexcept
	{
		return value <= rhs.value;
	}
	constexpr bool operator>( Degree rhs )const noexcept
	{
		return value > rhs.value;
	}
	constexpr bool operator>=( Degree rhs )const noexcept
	{
		return value >= rhs.value;
	}

private:
	friend constexpr auto operator*( float lhs, Degree rhs )noexcept;
	friend constexpr auto operator/( float lhs, Degree rhs )noexcept;
	float value = 0.f;
};

class Radian
{
public:
	Radian() = default;
	constexpr Radian( Degree value_ )noexcept;
	explicit constexpr Radian( float value_ )noexcept;
	constexpr operator float()const noexcept
	{
		return value;
	}

	constexpr Radian& operator+=( Radian rhs )noexcept
	{
		value += rhs.value;
		return *this;
	}
	constexpr Radian& operator-=( Radian rhs )noexcept
	{
		value -= rhs.value;
		return *this;
	}
	constexpr Radian& operator*=( float rhs )noexcept
	{
		value *= rhs;
		return *this;
	}
	constexpr Radian& operator/=( float rhs )noexcept
	{
		value /= rhs;
		return *this;
	}

	constexpr bool operator==( Radian rhs )const noexcept
	{
		return value == rhs.value;
	}
	constexpr bool operator!=( Radian rhs )const noexcept
	{
		return !( *this == rhs );
	}
	constexpr bool operator<( Radian rhs )const noexcept
	{
		return value < rhs.value;
	}
	constexpr bool operator<=( Radian rhs )const noexcept
	{
		return value <= rhs.value;
	}
	constexpr bool operator>( Radian rhs )const noexcept
	{
		return value > rhs.value;
	}
	constexpr bool operator>=( Radian rhs )const noexcept
	{
		return value >= rhs.value;
	}

	float Sin()const noexcept
	{
		return std::sin( value );
	}
	float Cos()const noexcept
	{
		return std::cos( value );
	}
private:
	friend constexpr auto operator*( float lhs, Radian rhs )noexcept;
	friend constexpr auto operator/( float lhs, Radian rhs )noexcept;
	float value = 0.f;
};



constexpr auto operator+( Degree lhs, Degree rhs )noexcept
{
	return lhs += rhs;
}
constexpr auto operator-( Degree lhs, Degree rhs )noexcept
{
	return lhs -= rhs;
}
constexpr auto operator*( Degree lhs, float rhs )noexcept
{
	return lhs *= rhs;
}
constexpr auto operator*( float lhs, Degree rhs )noexcept
{
	return Degree{ lhs * rhs.value };
}
constexpr auto operator/( Degree lhs, float rhs )noexcept
{
	return lhs /= rhs;
}
constexpr auto operator/( float lhs, Degree rhs )noexcept
{
	return Degree{ lhs / rhs.value };
}

constexpr auto operator+( Radian lhs, Radian rhs )noexcept
{
	return lhs += rhs;
}
constexpr auto operator-( Radian lhs, Radian rhs )noexcept
{
	return lhs -= rhs;
}
constexpr auto operator*( Radian lhs, float rhs )noexcept
{
	return lhs *= rhs;
}
constexpr auto operator*( float lhs, Radian rhs )noexcept
{
	return Radian{ lhs * rhs.value };
}
constexpr auto operator/( Radian lhs, float rhs )noexcept
{
	return lhs /= rhs;
}
constexpr auto operator/( float lhs, Radian rhs )noexcept
{
	return Radian{ lhs / rhs.value };
}


constexpr Degree::Degree( Radian rad ) noexcept
	:
	value( rad * deg_factor )
{
}
constexpr Degree::Degree( float value_ ) noexcept
	:
	value( value_ )
{
}

constexpr Radian::Radian( Degree deg ) noexcept
	:
	value( deg * rad_factor )
{
}
constexpr Radian::Radian( float value_ ) noexcept
	:
	value( value_ )
{
}

inline float Sin( Degree angle )noexcept
{
	return std::sin( angle * rad_factor );
}
inline float Cos( Degree angle )noexcept
{
	return std::cos( angle * rad_factor );
}

inline float Sin( Radian angle )noexcept
{
	return std::sin( angle );
}
inline float Cos( Radian angle )noexcept
{
	return std::cos( angle );
}
