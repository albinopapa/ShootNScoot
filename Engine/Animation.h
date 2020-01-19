#pragma once

#include "Surface.h"
#include <vector>

class Animation
{
public:
	Animation(
		int x,
		int y,
		int width,
		int height,
		int count,
		const Surface& sprite,
		float holdTime,
		Color chroma = Colors::Magenta );
	
private:
	friend class AnimationController;
	friend class AnimationView;

	std::vector<RectI> frames;
	Surface const& sprite;
	float holdTime = 0.f;
	int iCurFrame = 0;
	float curFrameTime = 0.0f;
	Color chroma = Colors::Magenta;
};