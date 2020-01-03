#pragma once

#include "Enumerations.h"
#include "Graphics.h"

namespace sns
{
	class World;

	class WorldView
	{
	public:
		void Draw( World const& model, Graphics& gfx )const noexcept;
	};
}
