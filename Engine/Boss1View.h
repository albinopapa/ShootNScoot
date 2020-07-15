#pragma once

#include "Bosses.h"
#include "Graphics.h"

class Boss1View
{
public:
	void Draw( Boss1 const& model, Graphics& gfx )const noexcept;

private:
	Surface	sprite = "Images/Enemy1Ship.png";
};
