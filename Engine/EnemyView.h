#pragma once

#include "Graphics.h"

namespace sns
{
	class Enemy;

	class EnemyView
	{
	public:
		static void Draw( Enemy const& model, Graphics& gfx )noexcept;
	};
}