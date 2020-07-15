#pragma once

#include "Enumerations.h"
#include "Graphics.h"
#include "World.h"

class WorldView
{
public:
	void Draw( World const& model, Graphics& gfx )const noexcept;
};
