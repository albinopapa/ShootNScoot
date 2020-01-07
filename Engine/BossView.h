#pragma once

#include "Graphics.h"

namespace sns
{
	struct Boss;
	struct Boss1;
	struct Boss2;

	class BossView
	{
	public:
		static void Draw( Boss const& model, Graphics& gfx )noexcept;
	private:
		static void Draw( Boss1 const& boss, Boss const& parent, Graphics& gfx )noexcept;
		static void Draw( Boss2 const& boss, Boss const& parent, Graphics& gfx )noexcept;
	};
}