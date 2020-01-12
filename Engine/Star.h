#pragma once

#include "Rect.h"
#include "Vec2.h"

namespace sns
{
	class Star
	{
	public:
		using Controller = struct StarController;
	public:
		void Update()noexcept;

	private:
		friend struct StarController;
		Vec2 position;
		float speed;
		static constexpr float radius = 1.f;
		static constexpr auto rect = RectF{ -radius, -radius, radius, radius };
	};
}
