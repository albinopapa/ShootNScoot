#pragma once

#include "Graphics.h"

namespace sns
{
	class Star;

	class StarView
	{
	public:
		void Draw( Star const& model, Graphics& gfx )const noexcept;
	};

}