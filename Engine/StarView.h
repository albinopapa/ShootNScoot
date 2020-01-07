#pragma once

#include "Graphics.h"

namespace sns
{
	class Star;

	class StarView
	{
	public:
		static void Draw( Star const& model, Graphics& gfx )noexcept;
	};

}