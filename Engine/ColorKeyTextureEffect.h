#pragma once

#include "BaseGeometryShader.h"
#include "BaseTextureVertexShader.h"
#include "Colors.h"
#include "RasterStates.h"
#include "Surface.h"

#include <cassert>

template<typename SamplerType>
struct ColorKeyTextureEffect
{
	using VertexShader = BaseTextureVertexShader;
	using Vertex = typename VertexShader::Vertex;
	using RasterState = RasterAlpha;
	using GeometryShader = BaseGeometryShader<Vertex>;

	struct PixelShader
	{
		struct ConstantBuffer
		{
			Color key;
			Color tint;
		};
		constexpr Color operator()( Vertex const& vin )const noexcept
		{
			assert( sprite != nullptr );
			const auto texcolor = sampler( *sprite, vin.texcoord );
			
			const auto a = texcolor.GetA();
			const auto r = ( texcolor.GetR() * buffer.tint.GetR() ) >> 8;
			const auto g = ( texcolor.GetG() * buffer.tint.GetG() ) >> 8;
			const auto b = ( texcolor.GetB() * buffer.tint.GetB() ) >> 8;
			return texcolor != buffer.key ? Color( a, r, g, b ) : Color( 0, r, g, b );
		}

		Surface const* sprite = nullptr;
		ConstantBuffer buffer;
		SamplerType sampler;
	};

	VertexShader vs;
	GeometryShader gs;
	PixelShader ps;
	RasterState rs;
};
