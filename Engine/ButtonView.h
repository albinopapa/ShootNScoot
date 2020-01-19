#pragma once

class Font;
class Surface;
namespace sns
{
	class Button;

	class ButtonView
	{
	public:
		static void Draw( Button const& model, Font const& font, Surface& render_target )noexcept;
	};
}