#pragma once

#include "Graphics.h"

namespace sns
{
	class Enemy;

	class EnemyView
	{
	public:
		void Draw( Enemy const& model, Graphics& gfx )const noexcept;

	private:
		Surface	sprite = "Images/Enemy1Ship.png";
	};
}