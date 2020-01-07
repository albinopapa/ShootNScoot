#pragma once

#include "Graphics.h"

namespace sns
{
	class Hero;

	class HeroView
	{
	public:
		static void Draw( Hero const& model, Graphics& gfx )noexcept;
	};
}