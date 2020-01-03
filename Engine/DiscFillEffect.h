#pragma once

#include "BaseGeometryShader.h"
#include "ColorVertex.h"
#include "Mat3.h"

struct DiscFillEffect
{
	using Vertex = ColorVertex;

	struct VertexShader
	{
		struct ConstantBuffer
		{
			Mat3F transform;
		};

		constexpr Vertex operator()( Vertex const& vin )const noexcept
		{
			return { buffer.transform * vin.position, vin.color };
		}

		ConstantBuffer buffer;
	};

	using GeometryShader = BaseGeometryShader<Vertex>;

	struct PixelShader
	{
		struct ConstantBuffer 
		{
			Vec2 center;
			float sqrRadius;
		};

		constexpr Color operator()( Vertex const& vin )const noexcept
		{
			if( ( vin.position - buffer.center ).LengthSq() < buffer.sqrRadius )
				return vin.color;
			else
				return Color( vin.color, 0 );
		}

		ConstantBuffer buffer;
	};

	VertexShader vs;
	GeometryShader gs;
	PixelShader ps;

};