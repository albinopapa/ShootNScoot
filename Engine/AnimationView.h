#pragma once

#include "Colors.h"
#include "ColorKeyTextureEffect.h"
#include "PointSampler.h"
#include "Vec2.h"

class Animation;
class Surface;

class AnimationView
{
public:
	static void Draw( Animation const& model, const Vec2& pos, Surface& render_target, Color tint = Colors::White )noexcept;

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