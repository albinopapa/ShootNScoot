#pragma once

#include "Mat3.h"
#include "Rect.h"
#include "Vec2.h"

namespace sns
{
	class Star
	{
	public:
		Star() = default;
		Star( Vec2 const& position_, float speed_ )noexcept;

	private:
		friend class StarController;
		friend class StarView;

		Vec2 position;
		float speed;
		static constexpr float radius = 1.f;
		static constexpr auto rect = RectF{ -radius, -radius, radius, radius };
	};
}
