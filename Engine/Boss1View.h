#pragma once

#include "Graphics.h"

namespace sns
{
	class Boss1;

	class Boss1View
	{
	public:
		void Draw( Boss1 const& model, Graphics& gfx )const noexcept;

	private:
		Surface	sprite = "Images/Enemy1Ship.png";
	};
}