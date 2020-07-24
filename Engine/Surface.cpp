#include "Surface.h"
#include "ChiliWin.h"
#include "WicWrapper.h"
#include <cassert>
#include <fstream>
#include <algorithm>

Surface::Surface( const std::string& filename )
{
	auto wic = Wic{};
	auto decoder = wic.create_decoder( std::wstring( filename.begin(), filename.end() ) );
	auto frame = wic.create_frame_decode( decoder.Get() );
	auto converter = wic.create_format_converter( frame.Get() );

	converter->GetSize(
		reinterpret_cast< UINT* >( &width ),
		reinterpret_cast< UINT* >( &height )
	);
	auto data = wic.copy_pixels_to_buffer( width, height, converter.Get() );

	pixels.reset( reinterpret_cast< Color* >( data.release() ) );
}

Surface::Surface( int width, int height )
	:
	width( width ),
	height( height ),
	pixels( std::make_unique<Color[]>( width* height ) )
{}

Surface::Surface( Surface&& donor )
	:
	width( donor.width ),
	height( donor.height ),
	pixels( std::move( donor.pixels ) )
{}

Surface& Surface::operator=( Surface&& rhs )
{
	if(this != &rhs)
	{
		width = rhs.width;
		height = rhs.height;
		pixels = std::move( rhs.pixels );
		rhs.width = 0;
		rhs.height = 0;
	}
	return *this;
}

void Surface::PutPixel( int x, int y, Color c )
{
	assert( x >= 0 );
	assert( y >= 0 );
	assert( x < width );
	assert( y < height );
	pixels[ x + ( y * width ) ] = c;
}

void Surface::PutPixelClipped( int x, int y, Color color ) noexcept
{
	if( x >= 0 && x < width && y >= 0 && y < height )
	{
		PutPixel( x, y, color );
	}
}

Color Surface::GetPixel( int x, int y ) const
{
	assert( x >= 0 );
	assert( y >= 0 );
	assert( x < width );
	assert( y < height );
	return pixels[ x + ( y * width ) ];
}

int Surface::GetWidth() const
{
	return width;
}

int Surface::GetHeight() const
{
	return height;
}

RectI Surface::GetRect() const
{
	return{ 0, 0, width, height };
}

void Surface::Fill( Color c )
{
	if( c.GetA() == 0 )
	{
		memset( pixels.get(), 0, sizeof( Color ) * width * height );
	}
	else if( c.GetB() == c.GetG() && c.GetB() == c.GetR() )
	{
		memset( pixels.get(), c.GetB(), sizeof( Color ) * width * height );
	}
	else
	{
		for( int y = 0; y < height; ++y )
		{
			for( int x = 0; x < width; ++x )
			{
				PutPixel( x, y, c );
			}
		}
	}
}

const Color* Surface::Data() const
{
	return pixels.get();
}

Color* Surface::Data()
{
	return pixels.get();
}
