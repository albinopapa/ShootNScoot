#pragma once

#include "Graphics.h"

namespace sns
{
	struct Boss;
	struct Boss1;
	struct Boss2;
	struct Boss3;
	struct Boss4;
	struct Boss5;
	struct Boss6;
	struct Boss7;
	struct Boss8;
	struct Boss9;
	struct Boss10;

	class BossView
	{
	public:
		static void Draw( Boss const& model, Graphics& gfx )noexcept;
	private:
		static void Draw( Boss1 const& boss, Boss const& parent, Graphics& gfx )noexcept;
		static void Draw( Boss2 const& boss, Boss const& parent, Graphics& gfx )noexcept;
		static void Draw( Boss3 const& boss, Boss const& parent, Graphics& gfx )noexcept;
		static void Draw( Boss4 const& boss, Boss const& parent, Graphics& gfx )noexcept;
		static void Draw( Boss5 const& boss, Boss const& parent, Graphics& gfx )noexcept;
		static void Draw( Boss6 const& boss, Boss const& parent, Graphics& gfx )noexcept;
		static void Draw( Boss7 const& boss, Boss const& parent, Graphics& gfx )noexcept;
		static void Draw( Boss8 const& boss, Boss const& parent, Graphics& gfx )noexcept;
		static void Draw( Boss9 const& boss, Boss const& parent, Graphics& gfx )noexcept;
		static void Draw( Boss10 const& boss, Boss const& parent, Graphics& gfx )noexcept;
	};
}