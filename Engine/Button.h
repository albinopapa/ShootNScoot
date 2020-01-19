#pragma once

#include "Colors.h"
#include "Vec2.h"

namespace sns
{
	class Button
	{
	public:
		static constexpr auto selected_color = Colors::Magenta;
		static constexpr auto deselected_color = Colors::White;
		const char* label = nullptr;
		Vec2 position;
		Color color = Colors::White;
	};
}
