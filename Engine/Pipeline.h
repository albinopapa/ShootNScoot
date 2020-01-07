#pragma once

#include "Triangle.h"
#include "PointSampler.h"
#include "ColorKeyTextureEffect.h"
#include "DiscFillEffect.h"
#include "NullPixelShader.h"
#include "RectFillEffect.h"

#include <algorithm>
#include <array>
#include <variant>

struct Pipeline
{
public:
	Pipeline( Color* pixels_, int stride_ )noexcept
		:
		pixels( pixels_ ),
		stride( stride_ )
	{}

	template<typename Effect, typename ConstantBuffer = typename Effect::VertexShader::ConstantBuffer>
	void VSSetConstantBuffer( Effect& effect, ConstantBuffer const& buffer_ )const noexcept
	{
		effect.vs.buffer = buffer_;
	}

	template<typename Effect, typename ConstantBuffer = typename Effect::PixelShader::ConstantBuffer>
	void PSSetConstantBuffer( Effect& effect, ConstantBuffer const& buffer_ )const noexcept
	{
		effect.ps.buffer = buffer_;
	}

	template<typename Effect>
	void PSSetTexture( Effect& effect, Surface const& sprite_ )const noexcept
	{
		effect.ps.sprite = std::addressof( sprite_ );
	}

	template<typename Effect>
	void Draw(
		Effect& effect,
		std::array<typename Effect::Vertex, 4> const& vertices)noexcept
	{
		// Run vertex shader
		const auto tvertices = DoVertexShader( effect, vertices );

		// Run geometry shader to create triangles
		const auto triangles = DoGeometryShader( effect, tvertices );

		for( auto const& triangle : triangles )
		{
			Rasterize( effect, triangle );
		}
	}

private:
	template<typename Effect>
	std::array<typename Effect::Vertex, 4> DoVertexShader(
		Effect const& effect,
		std::array<typename Effect::Vertex, 4> const& vertices )const noexcept
	{
		return std::array{
			effect.vs( vertices[ 0 ] ),
			effect.vs( vertices[ 1 ] ),
			effect.vs( vertices[ 2 ] ),
			effect.vs( vertices[ 3 ] )
		};
	}

	template<typename Vertex>
	RectF RasterBounds( Triangle<Vertex> const& triangle )const noexcept
	{
		// Find min and max vertices
		const auto[ xMin, xMax ] = std::minmax_element(
			triangle.v.begin(),
			triangle.v.end(),
			[]( const Vertex& left, const Vertex& right ) { return left.position.x < right.position.x; }
		);
		const auto[ yMin, yMax ] = std::minmax_element(
			triangle.v.begin(),
			triangle.v.end(),
			[]( const Vertex& left, const Vertex& right ) { return left.position.y < right.position.y; }
		);

		// Clamp to screen boundaries
		return {
			std::floor( std::max( xMin->position.x, 0.f ) ),
			std::floor( std::max( yMin->position.y, 0.f ) ),
			std::ceil( std::min( xMax->position.x, screenRect.Width() ) ),
			std::ceil( std::min( yMax->position.y, screenRect.Height() ) )
		};
	}

	template<typename Effect>
	std::array<Triangle<typename Effect::Vertex>, 2> DoGeometryShader(
		Effect const& effect,
		std::array<typename Effect::Vertex, 4> const& vertices )const noexcept
	{
		return{
			effect.gs( vertices[ 0 ], vertices[ 1 ], vertices[ 2 ] ),
			effect.gs( vertices[ 3 ], vertices[ 2 ], vertices[ 1 ] )
		};
	}

	template<typename Effect>
	void Rasterize(
		Effect& effect,
		Triangle<typename Effect::Vertex> const& triangle )
	{
		// Get bounding box around transformed quad
		const auto bounds = RasterBounds( triangle );

		// Early out if not in view at all
		if( !bounds.Overlaps( screenRect ) ) return;

		// Rasterize if point is in either triangle
		for( float y = bounds.top; y < bounds.bottom; ++y )
		{
			for( float x = bounds.left; x < bounds.right; ++x )
			{
				// Check if point is in triangle
				if( const auto coords = triangle.Contains( { x, y } ); coords.has_value() )
				{
					auto& pixel = pixels[ int( x ) + int( y ) * stride ];

					// Interpolate between the vertices of the triangle
					const auto vertex = triangle.Interpolate( *coords );

					pixel = AlphaBlend( effect.ps( vertex ), pixel );
				}
			}
		}
	}

private:
	Color* pixels = nullptr;
	int stride = 0;
};
