#pragma once

#include "BaseGeometryShader.h"
#include "Colors.h"
#include "Mat3.h"
#include "Surface.h"
#include "Triangle.h"
#include "TextureVertex.h"

#include <cassert>

template<typename SamplerType>
struct SolidTextureEffect
{
	using Vertex = TextureVertex;

	struct VertexShader
	{
		struct ConstantBuffer
		{
			Mat3F world;
		};
		Vertex operator()( Vertex const& vin )const noexcept
		{
			return { buffer.world * vin.position, vin.texcoord };
		}
		ConstantBuffer buffer;
	};

	using GeometryShader = BaseGeometryShader<Vertex>;

	struct PixelShader
	{
		struct ConstantBuffer{};

		Color operator()( Vertex const& vin )const noexcept
		{
			assert( sprite != nullptr );
			return sampler( *sprite, vin.texcoord );
		}

		Surface const* sprite = nullptr;
		SamplerType sampler;
	};

	VertexShader vs;
	GeometryShader gs;
	PixelShader ps;
};
