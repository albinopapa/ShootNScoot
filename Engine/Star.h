#pragma once

#include "Rect.h"
#include "Vec2.h"

namespace sns
{
	struct Star
	{
	public:
		void Update()noexcept;

	public:
		Vec2 position;
		float speed;
		static constexpr float radius = 1.f;
		static constexpr auto rect = RectF{ -radius, -radius, radius, radius };
	};
}
