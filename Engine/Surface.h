#pragma once

#include "Colors.h"
#include "Rect.h"
#include <string>
#include <vector>

class Surface
{
public:
	Surface() = default;
	Surface( const Surface& ) = default;
	Surface( Surface&& donor );

	Surface& operator=( const Surface& ) = default;
	Surface& operator=( Surface&& rhs );

private:
	friend class SurfaceController;

	std::vector<Color> pixels;
	int width = 0;
	int height = 0;
};
