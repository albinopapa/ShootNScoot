#pragma once

#include "Graphics.h"

namespace sns
{
	class Shield;

	class ShieldView
	{
	public:
		static void Draw( Shield const& model, Vec2 const& position, Graphics& gfx )noexcept;
	};
}