#pragma once

#include "Graphics.h"

namespace sns
{
	class Hero;

	class HeroView
	{
	public:
		void Draw( Hero const& model, Graphics& gfx )const noexcept;
	private:
		Surface	sprite = "Images/HeroShip.png";
	};
}