#pragma once

#include "Graphics.h"
#include "Star.h"

class StarView
{
public:
	void Draw( Star const& model, Graphics& gfx )const noexcept;
};
