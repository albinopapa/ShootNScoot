#pragma once

#include "DiscFillEffect.h"
#include "Surface.h"

namespace sns
{
	class Asteroid;

	class AsteroidView
	{
	public:
		static void Draw( Asteroid const& model, Surface& render_target )noexcept;
	private:
		using Effect = DiscFillEffect;
		static Effect effect;
		static constexpr Color color = Color{ 200, 100, 50 };
		static constexpr auto vertices = std::array{
			DiscFillEffect::Vertex{ { -.5f, -.5f }, color },
			DiscFillEffect::Vertex{ {  .5f, -.5f }, color },
			DiscFillEffect::Vertex{ { -.5f,  .5f }, color },
			DiscFillEffect::Vertex{ {  .5f,  .5f }, color }
		};
	};
}