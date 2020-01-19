#include "Animation.h"

Animation::Animation(
	int x,
	int y,
	int width,
	int height,
	int count,
	const Surface& sprite,
	float holdTime,
	Color chroma )
	:
	frames( count ),
	sprite( sprite ),
	holdTime( holdTime ),
	chroma( chroma )
{
	int i = 0;
	for( auto& frame : frames )
	{
		const auto j = i + 1;
		const auto left = x + i * width;
		const auto top = y;
		const auto right = x + j * width;
		const auto bottom = y + height;
		++i;

		frame = { left, top, right, bottom };
	}
}

