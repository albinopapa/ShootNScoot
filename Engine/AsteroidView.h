#pragma once

#include "Graphics.h"

namespace sns
{
	class Asteroid;

	class AsteroidView
	{
	public:
		void Draw( Asteroid const& model, Graphics& gfx )const noexcept;
	private:
		static constexpr Color color = Color{ 200, 100, 50 };
	};
}