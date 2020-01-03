#pragma once

#include "Graphics.h"

namespace sns
{
	class Ammo;
	class AmmoView
	{
	public:
		void Draw( Ammo const& model, Graphics& gfx )const noexcept;
	};
}