#pragma once

#include "Colors.h"

namespace sns
{
	class Button;

	class ButtonController
	{
	public:
		static void Select( Button& model )noexcept;
		static void Deselect( Button& model )noexcept;
	};
}