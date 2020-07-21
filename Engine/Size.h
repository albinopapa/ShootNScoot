#pragma once

template<typename T>
struct Size {
	T width = {};
	T height = {};
};

using SizeI = Size<int>;
using SizeF = Size<float>;

template<typename T>
constexpr Vec2_<T> operator+( Vec2_<T> const& lhs, Size<T> const& rhs )noexcept {
	return{ lhs.x + rhs.width, lhs.y + rhs.height };
}

template<typename T>
constexpr Vec2_<T> operator-( Vec2_<T> const& lhs, Size<T> const& rhs )noexcept {
	return{ lhs.x - rhs.width, lhs.y - rhs.height };
}

template<typename T>
constexpr Size<T> operator*( Size<T> const& lhs, T rhs )noexcept {
	return{ lhs.width * rhs, lhs.height * rhs };
}

template<typename T>
constexpr Size<T> operator/( Size<T> const& lhs, T rhs )noexcept {
	return{ lhs.width / rhs, lhs.height / rhs };
}
