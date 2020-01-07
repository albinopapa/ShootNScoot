#pragma once

#include "Rect.h"

namespace sns
{
	class Boss;
	class Boss1;
	class Boss2;

	class World;

	class BossController
	{
	public:
		static void Update( Boss& model, World& world_model, float dt)noexcept;
		static void TakeDamage( Boss& model, float amount )noexcept;

		static RectF AABB( Boss const& model )noexcept;
		static float Damage( Boss const& model )noexcept;
		static float Health( Boss const& model )noexcept;

	private:
		static void Update( Boss1& model, World& world, Boss& parent, float dt )noexcept;
		static void Update( Boss2& model, World& world, Boss& parent, float dt )noexcept;
	};
}
