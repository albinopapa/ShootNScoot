#pragma once
#include "Star.h"
#include "Graphics.h"

	class StarView
	{
	public:
		void Draw( Star const& model, Graphics& gfx )const noexcept;
	};
