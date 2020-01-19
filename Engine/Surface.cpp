#include "Surface.h"
#include <utility>

Surface::Surface( Surface&& donor )
	:
	width( donor.width ),
	height( donor.height ),
	pixels( std::move( donor.pixels ) )
{
}

Surface& Surface::operator=( Surface&& rhs )
{
	if( this != std::addressof( rhs ) )
	{
		width = rhs.width;
		height = rhs.height;
		pixels = std::move( rhs.pixels );

		rhs.width = 0;
		rhs.height = 0;
	}

	return *this;
}
