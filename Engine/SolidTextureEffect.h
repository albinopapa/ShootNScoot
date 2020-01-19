#pragma once

#include "Colors.h"
#include "Mat3.h"
#include "Surface.h"
#include "Triangle.h"
#include "TextureVertex.h"
#include <array>
#include <cassert>

template<typename SamplerType>
class SolidTextureEffect
{
public:
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
	struct GeometryShader
	{
		constexpr Triangle<TextureVertex> operator()( Vertex const& v0, Vertex const& v1, Vertex const& v2 )const noexcept
		{
			return{ v0, v1, v2 };
		}
	};
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
		ConstantBuffer buffer;
	};

private:
	friend class EffectController;
	friend class EffectView;

	std::array<Vertex, 4> vertices;

	VertexShader vs;
	GeometryShader gs;
	PixelShader ps;
};
