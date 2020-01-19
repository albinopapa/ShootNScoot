#pragma once

#include "Rect.h"
#include "Vec2.h"

namespace sns
{
	class Shield;

	class ShieldController
	{
	public:
		static void Update( Shield& model, Vec2 const& position, float dt )noexcept;

		static void TakeDamage( Shield& model, float amount )noexcept;
		static RectF AABB( Shield const& model, Vec2 position )noexcept;
		static float Health( Shield const& model )noexcept;
		static void Reset( Shield& model )noexcept;
	};
}