#pragma once

#include "BaseGeometryShader.h"
#include "Colors.h"
#include "ColorController.h"
#include "Mat3.h"
#include "Surface.h"
#include "TextureVertex.h"
#include <array>
#include <cassert>

template<typename SamplerType>
class ColorKeyTextureEffect
{
public:
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
			Color key = Colors::Magenta;
			Color tint = Colors::White;
		};
		constexpr Color operator()( Vertex const& vin )const noexcept
		{
			assert( sprite != nullptr );
			const auto texcolor = sampler( *sprite, vin.texcoord );
			const auto a = ( 
				ColorController::GetA( texcolor ) * 
				ColorController::GetA( buffer.tint ) ) >> 8;
			const auto r = ( 
				ColorController::GetR( texcolor ) * 
				ColorController::GetR( buffer.tint ) ) >> 8;
			const auto g = ( 
				ColorController::GetG( texcolor ) * 
				ColorController::GetG( buffer.tint ) ) >> 8;
			const auto b = ( 
				ColorController::GetB( texcolor ) * 
				ColorController::GetB( buffer.tint ) ) >> 8;

			return ( texcolor == buffer.key ) ?
				Color( 0, r, g, b ) : Color( a, r, g, b );
		}

		Surface const* sprite = nullptr;
		ConstantBuffer buffer;
		SamplerType sampler;
	};

private:
	friend class EffectController;
	friend class EffectView;

	std::array<Vertex, 4> vertices;

	VertexShader vs;
	GeometryShader gs;
	PixelShader ps;
};
