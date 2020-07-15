#pragma once

template<typename T>
struct Size {
	T width = {};
	T height = {};
};

using SizeI = Size<int>;
using SizeF = Size<float>;