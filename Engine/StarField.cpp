#include "Starfield.h"

namespace sns
{
	std::vector<Star> Starfield::generate(
		RectF position_bounds,
		std::pair<float, float> speed_bounds,
		int count )
	{
		std::mt19937 rng;
		auto xDist = std::uniform_real_distribution<float>{ position_bounds.left,position_bounds.right };
		auto yDist = std::uniform_real_distribution<float>{ position_bounds.top,position_bounds.bottom };
		auto spdDist = std::uniform_real_distribution<float>{ speed_bounds.first, speed_bounds.second };

		auto stars = std::vector<Star>{ size_t( count ) };

		for( auto& star : stars )
		{
			star = Star{ Vec2{xDist( rng ), yDist( rng )}, spdDist( rng ) };
		}

		return stars;
	}

	Star Starfield::generate_star( std::mt19937& rng, std::pair<float, float> width_bounds, std::pair<float, float> speed_bounds )noexcept
	{
		auto xDist = std::uniform_real_distribution<float>{ width_bounds.first, width_bounds.second };
		auto spdDist = std::uniform_real_distribution<float>{ speed_bounds.first, speed_bounds.second };

		return Star{ Vec2{xDist( rng ), 0.f}, spdDist( rng ) };
	}

}
