#pragma once

template<typename T>
struct Size {
	Size() = default;
	constexpr Size( T width_, T height_ )noexcept
		:
		width( width_ ),
		height( height_ )
	{}
	template<typename U>
	constexpr Size( Size<U> const& rhs )noexcept
		:
		width( T( rhs.width ) ),
		height( T( rhs.height ) )
	{}

	T width = T( 0 );
	T height = T( 0 );
};

template<typename T>
constexpr auto operator+( Size<T> const& lhs, Size<T> const& rhs )noexcept
{
	return Size<T>{ lhs.width + rhs.width, lhs.height + rhs.height };
}

template<typename T>
constexpr auto operator-( Size<T> const& lhs, Size<T> const& rhs )noexcept
{
	return Size<T>{ lhs.width - rhs.width, lhs.height - rhs.height };
}

template<typename T>
constexpr auto operator*( Size<T> const& lhs, T rhs )noexcept
{
	return Size<T>{ lhs.width * rhs, lhs.height * rhs };
}


using SizeI = Size<int>;
using SizeF = Size<float>;