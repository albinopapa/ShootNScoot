#pragma once

#include "ColorKeyTextureEffect.h"
#include "PointSampler.h"
#include <array>

class Surface;
namespace sns
{
	class Ammo;
	class AmmoView
	{
	public:
		static void Draw( Ammo const& model, Surface& render_target )noexcept;

	private:
		using Effect = ColorKeyTextureEffect<PointSampler>;
		static Effect effect;
		static constexpr auto vertices = std::array{
			Effect::Vertex{ {-.5f, -.5f }, { 0.f, 0.f } },
			Effect::Vertex{ { .5f, -.5f }, { 1.f, 0.f } },
			Effect::Vertex{ {-.5f,  .5f }, { 0.f, 1.f } },
			Effect::Vertex{ { .5f,  .5f }, { 1.f, 1.f } }
		};

	};
}