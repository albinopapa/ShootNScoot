#pragma once

#include "Graphics.h"
#include "Hero.h"
#include "SpriteCache.h"

class HeroView
{
public:
	void Draw( Hero const& model, SpriteCache const& cache, Graphics& gfx )const noexcept;
};
