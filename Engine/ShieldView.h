#pragma once

#include "Graphics.h"

namespace sns
{
	class Shield;

	class ShieldView
	{
	public:
		void Draw( Vec2 const& position, Shield const& model, Graphics& gfx )const noexcept;

	private:
		static const Surface sprite;
	};
}