#pragma once

#include "Graphics.h"
#include "Triangle.h"
#include <algorithm>

template<typename Effect>
struct Pipeline
{
public:
	using Vertex = typename Effect::Vertex;
	using VSConstantBuffer = typename Effect::VertexShader::ConstantBuffer;
	using PSConstantBuffer = typename Effect::PixelShader::ConstantBuffer;
public:
	Pipeline( Effect const& effect_, Graphics& gfx_ )
		:
		effect( effect_ ),
		gfx( gfx_ )
	{}

	void PSSetConstantBuffer( PSConstantBuffer const& buffer_ )noexcept
	{
		effect.ps.buffer = buffer_;
	}
	void PSSetTexture( Surface const& sprite_ )noexcept
	{
		effect.ps.sprite = std::addressof( sprite_ );
	}

	void Draw( RectF const& dst, Radian angle )noexcept
	{
		VSSetConstantBuffer( {
				Mat3F::Rotate( angle ) *
				Mat3F::Scale( dst.Width(), dst.Height() ) *
				Mat3F::Translation( dst.Center() ) 
			} );

		const Vertex tvertices[] = {
			effect.vs( vertices[ 0 ] ),
			effect.vs( vertices[ 1 ] ),
			effect.vs( vertices[ 2 ] ),
			effect.vs( vertices[ 3 ] )
		};

		auto xLess = []( const Vertex& left, const Vertex& right )
		{
			return left.position.x < right.position.x;
		};
		auto yLess = []( const Vertex& left, const Vertex& right )
		{
			return left.position.y < right.position.y;
		};

		const auto[ xMin, xMax ] = 
			std::minmax_element( &tvertices[ 0 ], &tvertices[ 3 ], xLess );
		const auto[ yMin, yMax ] = 
			std::minmax_element( &tvertices[ 0 ], &tvertices[ 3 ], yLess );

		const auto xStart = std::floor( std::max( xMin->position.x, 0.f ) );
		const auto yStart = std::floor( std::max( yMin->position.y, 0.f ) );
		const auto xEnd = std::ceil( std::min( xMax->position.x, screenRect.Width() ) );
		const auto yEnd = std::ceil( std::min( yMax->position.y, screenRect.Height() ) );
		
		const auto triangle0 =
			effect.gs( tvertices[ 0 ], tvertices[ 1 ], tvertices[ 2 ] );
		const auto triangle1 =
			effect.gs( tvertices[ 3 ], tvertices[ 2 ], tvertices[ 1 ] );

		for( float y = yStart; y < yEnd; ++y )
		{
			for( float x = xStart; x < xEnd; ++x )
			{
				const auto p = Vec2{ x, y };
				if( !Rasterize( p, triangle0 ) )
				{
					Rasterize( p, triangle1 );
				}
			}
		}
	}

private:
	bool Rasterize( Vec2 const& p, Triangle<Vertex> const& triangle )noexcept
	{
		auto coords				= triangle.Contains( p );

		if( !coords.has_value() ) return false;

		const auto ix			= int( p.x );
		const auto iy			= int( p.y );
		const auto vertex		= triangle.Interpolate( *coords );
		const auto effect_color = effect.ps( vertex );
		const auto bg_color		= gfx.GetPixel( ix, iy );
		const auto dst_color	= AlphaBlend( effect_color, bg_color );

		gfx.PutPixel( ix, iy, dst_color );

		return true;
	}
	void VSSetConstantBuffer( VSConstantBuffer const& buffer_ )noexcept
	{
		effect.vs.buffer = buffer_;
	}

public:
	Graphics& gfx;
	Effect effect;
	Vertex vertices[ 4 ];
};
