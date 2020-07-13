#pragma once

#include "Rect.h"
#include "Star.h"
#include <random>
#include <utility>
#include <vector>

namespace sns
{
	class Starfield
	{
	public:
		static std::vector<Star> generate(
			RectF position_bounds,
			std::pair<float, float> speed_bounds,
			int count );

		static Star generate_star( std::mt19937& rng, std::pair<float, float> width_bounds, std::pair<float, float> speed_bounds )noexcept;

	};
}