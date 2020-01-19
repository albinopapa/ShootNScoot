#pragma once

#include "BaseGeometryShader.h"
#include "ColorVertex.h"
#include "Mat3.h"
#include <array>

class ShieldEffect
{
public:
	using Vertex = ColorVertex;

	struct VertexShader
	{
		struct ConstantBuffer
		{
			Mat3F world;
		};

		constexpr Vertex operator()( Vertex const& vin )const noexcept
		{
			return { transform.world * vin.position, vin.color };
		}

		ConstantBuffer transform;
	};

	using GeometryShader = BaseGeometryShader<Vertex>;

	struct PixelShader
	{
		struct ConstantBuffer
		{
			Vec2 center;
			Color color;
			float sqrRadius = 0.f;
		};
		constexpr Color operator()( Vertex const& vin )const noexcept
		{
			const auto sqrDist = 
				sqr( vin.position.x - buffer.center.x ) + 
				sqr( vin.position.y - buffer.center.y );

			const auto a = ( uint8_t( ( sqrDist * 255.f ) / buffer.sqrRadius ) );

			return sqrDist <= buffer.sqrRadius ? Color( buffer.color, a ) : Color( buffer.color, 0 );
		}

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