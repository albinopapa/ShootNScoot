#pragma once

#include "BaseGeometryShader.h"
#include "Colors.h"
#include "Mat3.h"
#include "Surface.h"
#include "TextureVertex.h"

#include <cassert>

template<typename SamplerType>
struct ColorKeyTextureEffect
{
	using Vertex = TextureVertex;

	struct VertexShader
	{
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
			return ( texcolor == buffer.key ) ? Color( 0, r, g, b ) : Color( a, r, g, b );
		}

		ConstantBuffer buffer;
		Surface const* sprite = nullptr;
		SamplerType sampler;
	};

	VertexShader vs;
	GeometryShader gs;
	PixelShader ps;
};
