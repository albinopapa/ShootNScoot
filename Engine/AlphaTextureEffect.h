#pragma once

#include "BaseGeometryShader.h"
#include "BaseTextureVertexShader.h"
#include "Colors.h"
#include "Mat3.h"
#include "RasterStates.h"
#include "Surface.h"
#include "Triangle.h"
#include "TextureVertex.h"
#include <cassert>

template<typename SamplerType>
struct AlphaTextureEffect
{
	using VertexShader = BaseTextureVertexShader;
	using Vertex = typename BaseTextureVertexShader::Vertex;
	using RasterState = RasterAlpha;

	using GeometryShader = BaseGeometryShader<Vertex>;

	struct PixelShader
	{
		struct ConstantBuffer {
		};

		Color operator()( Vertex const& vin )const noexcept
		{
			assert( sprite != nullptr );
			return sampler( *sprite, vin.texcoord );
		}

		Surface const* sprite = nullptr;
		SamplerType sampler;
	};

	RasterState rs;
	VertexShader vs;
	GeometryShader gs;
	PixelShader ps;
};

template<typename SamplerType>
class AlphaTextureSpriteSheetEffect {
public:
	using VertexShader = BaseTextureVertexShader;
	using Vertex = typename BaseTextureVertexShader::Vertex;
	using RasterState = RasterAlpha;

	using GeometryShader = BaseGeometryShader<Vertex>;

	struct PixelShader
	{
		struct ConstantBuffer {
		};

		Color operator()( Vertex const& vin )const noexcept
		{
			assert( sprite != nullptr );
			return sampler( *sprite, vin.texcoord );
		}

		Surface const* sprite = nullptr;
		SamplerType sampler;
	};

	RasterState rs;
	VertexShader vs;
	GeometryShader gs;
	PixelShader ps;

};