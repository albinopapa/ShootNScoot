#pragma once

#include "Mat3.h"
#include "TextureVertex.h"

struct BaseTextureVertexShader
{
	using Vertex = TextureVertex;
	struct ConstantBuffer
	{
		Mat3F world;
	};
	constexpr Vertex operator()( Vertex const& vin )const noexcept
	{
		return { buffer.world * vin.position, vin.texcoord };
	}
	ConstantBuffer buffer;
};

