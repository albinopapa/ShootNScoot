#pragma once

#include "Colors.h"

struct NullVertex {};
template<typename Vertex = NullVertex>
struct NullPixelShader
{
	constexpr Color operator()( Vertex const& vin )const noexcept
	{
		return Colors::Black;
	}
};