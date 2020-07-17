#pragma once

#include "Enumerations.h"
#include "Graphics.h"
#include "World.h"
#include "SpriteCache.h"

class WorldView
{
public:
	void Draw( World const& model, Graphics& gfx )const noexcept;
	SpriteCache sprites;
};
