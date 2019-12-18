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

	pixels.resize( width * height );
	memcpy( pixels.data(), data.get(), width * height * sizeof( Color ) );
}

Surface::Surface( int width,int height )
	:
	width( width ),
	height( height ),
	pixels( width * height )
{}

Surface::Surface( Surface&& donor )
{
	*this = std::move( donor );
}

Surface& Surface::operator=( Surface&& rhs )
{
	width = rhs.width;
	height = rhs.height;
	pixels = std::move( rhs.pixels );
	rhs.width = 0;
	rhs.height = 0;
	return *this;
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

const Color* Surface::Data() const
{
	return pixels.data();
}