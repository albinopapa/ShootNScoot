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
		static constexpr int herohalfwidth = 5,herohalfheight=10;

		//Surface	sprite = "Images/HeroShip.png";
	};
}