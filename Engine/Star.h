#pragma once

#include "Colors.h"
#include "Rect.h"
#include "Vec2.h"

namespace sns
{
	class Star
	{
	public:
		void Update()noexcept;

		static constexpr float radius = 1.f;
		static constexpr auto rect = RectF{ -radius, -radius, radius, radius };

		Vec2 position;
		float speed;
	};
}
