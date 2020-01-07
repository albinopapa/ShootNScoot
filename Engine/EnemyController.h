#pragma once

#include "Rect.h"

namespace sns
{
	class Enemy;

	class EnemyController
	{
	public:
		static void Update( Enemy& model, float dt )noexcept;
		static void TakeDamage( Enemy& model, float amount )noexcept;

		static RectF AABB( Enemy const& model )noexcept;
		static float Health( Enemy const& model )noexcept;
		static float Damage( Enemy const& model )noexcept;
		static bool IsAlive( Enemy const& model )noexcept;
	};
}