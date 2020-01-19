#pragma once

#include "ColorKeyTextureEffect.h"
#include "PointSampler.h"

#include "ColorController.h"
#include "Rect.h"
#include "RectController.h"
#include "SurfaceController.h"
#include "Triangle.h"
#include <algorithm>
#include <array>

class EffectView
{
public:
	template<typename Effect>
	static void Draw( Effect const& model, Surface& render_target )noexcept
	{
		// Run vertex shader
		const auto tvertices = DoVertexShader( model );

		// Run geometry shader to create triangles
		const auto triangles = DoGeometryShader( model, tvertices );

		for( auto const& triangle : triangles )
		{
			Rasterize( model, triangle, render_target );
		}
	}

private:
	template<typename Effect>
	static std::array<typename Effect::Vertex, 4> DoVertexShader( Effect const& model )noexcept
	{
		return std::array{
			model.vs( model.vertices[ 0 ] ),
			model.vs( model.vertices[ 1 ] ),
			model.vs( model.vertices[ 2 ] ),
			model.vs( model.vertices[ 3 ] )
		};
	}

	template<typename Vertex>
	static RectF RasterBounds( Triangle<Vertex> const& triangle, RectF const& surface_rect )noexcept
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

		// Clamp to render target boundaries
		return {
			std::floor( std::max( xMin->position.x, surface_rect.left ) ),
			std::floor( std::max( yMin->position.y, surface_rect.top ) ),
			std::ceil( std::min( xMax->position.x, surface_rect.right ) ),
			std::ceil( std::min( yMax->position.y, surface_rect.bottom ) )
		};
	}

	template<typename Effect>
	static std::array<Triangle<typename Effect::Vertex>, 2> DoGeometryShader(
		Effect const& model,
		std::array<typename Effect::Vertex, 4> const& vertices )noexcept
	{
		return{
			model.gs( vertices[ 0 ], vertices[ 1 ], vertices[ 2 ] ),
			model.gs( vertices[ 3 ], vertices[ 2 ], vertices[ 1 ] )
		};
	}

	template<typename Effect>
	static Color DoPixelShader(
		Effect const& model,
		typename Effect::Vertex const& vertex,
		Point const& position,
		Surface const& render_target )noexcept
	{
		return ColorController::AlphaBlend(
			model.ps( vertex ),
			SurfaceController::GetPixel( render_target, position )
		);
	}

	template<typename Effect>
	static void Rasterize(
		Effect const& model,
		Triangle<typename Effect::Vertex> const& triangle,
		Surface& render_target )noexcept
	{
		const auto rtRect = SurfaceController::GetRect( render_target );

		// Get bounding box around transformed quad
		const auto bounds = RasterBounds( triangle, rtRect );

		// Early out if not in view at all
		if( !RectController::Overlaps( bounds, rtRect ) ) return;

		const auto offset = Vec2{ rtRect.right, rtRect.bottom };

		// Rasterize if point is in either triangle
		for( Vec2 p = { bounds.left, bounds.top }; p.y < bounds.bottom; ++p.y )
		{
			for( p.x = bounds.left; p.x < bounds.right; ++p.x )
			{
				// Check if point is in triangle
				const auto coords = triangle.Contains( p );
				if( !coords.has_value() ) continue;

				// Interpolate between the vertices of the triangle
				const auto vertex = triangle.Interpolate( *coords );
				const auto position = Point( p + offset );

				const auto pixel = DoPixelShader( model, vertex, position, render_target );
				SurfaceController::PutPixel( render_target, position, pixel );
			}
		}
	}
};
