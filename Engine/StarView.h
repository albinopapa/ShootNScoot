#pragma once

#include "RectFillEffect.h"

class Surface;
namespace sns
{
	class Star;

	class StarView
	{
	public:
		static void Draw( Star const& model, Surface& render_target )noexcept;

	private:
		using Effect = RectFillEffect;
		static constexpr auto vertices = std::array{
			Effect::Vertex{ {-.5f, -.5f }, Colors::White},
			Effect::Vertex{ { .5f, -.5f }, Colors::White},
			Effect::Vertex{ {-.5f,  .5f }, Colors::White},
			Effect::Vertex{ { .5f,  .5f }, Colors::White},
		};

		static RectFillEffect effect;
	};

}