#pragma once

#include "Graphics.h"
#include "Vec2.h"

#include <random>
#include <vector>

namespace sns
{
	struct Star
	{
		Vec2 position;
		float speed;
	};

	struct StarField
	{
	public:
		StarField();
		void Update()noexcept;
		void Draw( Graphics& gfx )const noexcept;

	public:
		std::mt19937 rng;
		std::uniform_real_distribution<float> xDist = std::uniform_real_distribution<float>{ 0.f, float( Graphics::ScreenWidth - 1 ) };
		std::uniform_real_distribution<float> yDist = std::uniform_real_distribution<float>{ 0.f, float( Graphics::ScreenHeight - 1 ) };
		std::uniform_real_distribution<float> spdDist = std::uniform_real_distribution<float>{ 1.f, 2.f };
		std::vector<Star> stars = std::vector<Star>{ 250 };
	};
}
