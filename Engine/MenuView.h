#pragma once

class Font;
class Surface;
namespace sns
{
	class Menu;

	class MenuView
	{
	public:
		static void Draw( Menu const& model, Font const& font, Surface& render_target )noexcept;
	};
}