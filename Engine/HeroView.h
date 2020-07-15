#pragma once

#include "Graphics.h"
#include "Hero.h"

class HeroView
{
public:
	void Draw( Hero const& model, Graphics& gfx )const noexcept;
private:
	Surface	sprite = "Images/HeroShip.png";
};
