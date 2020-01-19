#pragma once

#include "ColorKeyTextureEffect.h"
#include "PointSampler.h"
#include "Vec2.h"
#include <array>
#include <string>

class Color;
class Font;
class Surface;

class FontView
{
public:
	static void Draw( Font const& model, const std::string& text, Vec2 const& pos, Color color, Surface& render_target )noexcept;

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