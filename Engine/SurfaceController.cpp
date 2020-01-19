#include "AngleMath.h"
#include "ChiliWin.h"
#include "ColorController.h"
#include "ColorKeyTextureEffect.h"
#include "DiscFillEffect.h"
#include "EffectController.h"
#include "EffectView.h"
#include "PointSampler.h"
#include "RectController.h"
#include "RectFillEffect.h"
#include "SurfaceController.h"
#include "Surface.h"
#include "Vec2Controller.h"
#include "WicWrapper.h"
#include <cassert>

Surface SurfaceController::CreateSurface( const std::string & filename )
{
	auto wic = Wic{};
	auto decoder = wic.create_decoder( std::wstring( filename.begin(), filename.end() ) );
	auto frame = wic.create_frame_decode( decoder.Get() );
	auto converter = wic.create_format_converter( frame.Get() );

	int width, height;
	converter->GetSize(
		reinterpret_cast< UINT* >( &width ),
		reinterpret_cast< UINT* >( &height )
	);

	auto data = wic.copy_pixels_to_buffer( width, height, converter.Get() );

	auto pixels = std::vector<Color>( width * height );
	memcpy( pixels.data(), data.get(), width * height * sizeof( Color ) );

	Surface s;
	s.width = width;
	s.height = height;
	s.pixels = std::move( pixels );

	return s;
}

Surface SurfaceController::CreateSurface( int width, int height )
{
	Surface s;
	s.width = width;
	s.height = height;
	s.pixels = std::vector<Color>( width * height );
	return s;
}

void SurfaceController::PutPixel( Surface & model, Point const& position, Color c ) noexcept
{
	assert( position.x >= 0 );
	assert( position.y >= 0 );
	assert( position.x < model.width );
	assert( position.y < model.height );
	model.pixels[ position.x + ( position.y * model.width ) ] = c;
}

Color SurfaceController::GetPixel( Surface const & model, Point const& position ) noexcept
{
	assert( position.x >= 0 );
	assert( position.y >= 0 );
	assert( position.x < model.width );
	assert( position.y < model.height );
	return model.pixels[ position.x + ( position.y * model.width ) ];
}

int SurfaceController::GetWidth( Surface const & model ) noexcept
{
	return model.width;
}

int SurfaceController::GetHeight( Surface const & model ) noexcept
{
	return model.height;
}

RectF SurfaceController::GetRect( Surface const & model ) noexcept
{
	const auto iRect = RectI{ { model.width, model.height } };
	const auto offset = RectController::Center( iRect );
	return RectF{ iRect - offset };
}

void SurfaceController::Fill( Surface& model, Color c ) noexcept
{
	if( ColorController::GetA( c ) == 0 )
	{
		memset( model.pixels.data(), 0, sizeof( Color ) * model.width * model.height );
	}
	else if( ColorController::GetB( c ) == ColorController::GetG( c ) &&
		ColorController::GetB( c ) == ColorController::GetR( c ) )
	{
		memset( 
			model.pixels.data(), 
			ColorController::GetB(c), 
			sizeof( Color ) * model.width * model.height 
		);
	}
	else
	{
		for( int y = 0; y < model.height; ++y )
		{
			for( int x = 0; x < model.width; ++x )
			{
				model.pixels[ x + ( y * model.width ) ] = c;
			}
		}
	}
}

const Color * SurfaceController::Data( Surface const & model ) noexcept
{
	return model.pixels.data();
}

// SAVE: May be useful later on

//void SurfaceController::DrawLine( Surface& model, Vec2 const& p0, Vec2 const& p1, float thickness, Color color )noexcept
//{
//	using Effect = RectFillEffect;
//	using Vertex = Effect::Vertex;
//	thickness = std::max( thickness, 1.f );
//
//	const auto delta = ( p1 - p0 );
//	const auto center = p0 + ( delta * .5f );
//	const auto size = Vec2{ Vec2Controller::Length( delta ) * .5f, thickness * .5f };
//
//	const auto dst = RectF{ center - size, center + size };
//	const auto angle = Radian{ std::atan2( delta.y, delta.x ) };
//
//	const auto width = RectController::Width( dst );
//	const auto height = RectController::Height( dst );
//	const auto center = RectController::Center( dst );
//
//	Effect effect;
//
//	EffectController::VSSetVertexBuffer( effect, {
//		Vertex{ { -.5f, -.5f }, color },
//		Vertex{ {  .5f, -.5f }, color },
//		Vertex{ { -.5f,  .5f }, color },
//		Vertex{ {  .5f,  .5f }, color }
//		} );
//
//	EffectController::VSSetConstantBuffer( effect, {
//			Mat3F::Rotate( angle ) *
//			Mat3F::Scale( width, height ) *
//			Mat3F::Translation( center )
//		} );
//
//	EffectView::Draw( effect, model );
//}
