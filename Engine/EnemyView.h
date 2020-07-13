#pragma once
#include "Enemies.h"
#include "Graphics.h"

	class EnemyView
	{
	public:
		void Draw( Enemy const& model, Graphics& gfx )const noexcept;

	private:
		Surface	sprite = "Images/Enemy1Ship.png";
	};
