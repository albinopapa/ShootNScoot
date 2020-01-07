#pragma once

#include "Enumerations.h"
#include "Graphics.h"

namespace sns
{
	class World;

	class WorldView
	{
	public:
		static void Draw( World const& model, Graphics& gfx )noexcept;
	};
}
