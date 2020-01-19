#pragma once

#include "BaseGeometryShader.h"
#include "ColorVertex.h"
#include "Mat3.h"
#include <array>

class RectFillEffect
{
public:
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
		struct ConstantBuffer{};

		constexpr Color operator()( Vertex const& vin )const noexcept
		{
			return vin.color;
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

