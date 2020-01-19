#pragma once

#include "EntityController.h"
#include "Rect.h"

namespace sns
{
	class Enemy;

	template<> class EntityController<Enemy>
	{
	public:
		static void Update( Enemy& model, float dt )noexcept;
		static void TakeDamage( Enemy& model, float amount )noexcept;

		static RectF AABB( Enemy const& model )noexcept;
		static float Health( Enemy const& model )noexcept;
		static float Damage( Enemy const& model )noexcept;
		static bool IsAlive( Enemy const& model )noexcept;
		static Vec2 const& Position( Enemy const& model )noexcept;
	};
}