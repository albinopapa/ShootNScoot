#pragma once

#include "Triangle.h"

template<typename Vertex>
struct BaseGeometryShader
{
	Triangle<Vertex> operator()( Vertex const& v0, Vertex const& v1, Vertex const& v2 )const noexcept
	{
		return { v0, v1, v2 };
	}
};