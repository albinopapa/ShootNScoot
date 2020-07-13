#pragma once

#include "Rect.h"
#include "Vec2.h"

namespace sns
{
	class Shield;

	class ShieldController
	{
	public:
		void Update( Shield& model, Vec2 const& position, float dt )noexcept;

		void TakeDamage( Shield& model, float amount )noexcept;
		RectF AABB( Shield& model, Vec2 position )const noexcept;
		float Health( Shield& model )const noexcept;
	};
}