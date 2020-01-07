#pragma once

#include "Graphics.h"

namespace sns
{
	class Ammo;
	class AmmoView
	{
	public:
		static void Draw( Ammo const& model, Graphics& gfx )noexcept;
	};
}