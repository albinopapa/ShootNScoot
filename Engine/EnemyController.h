#pragma once

#include "Rect.h"

namespace sns
{
	class Enemy;

	class EnemyController
	{
	public:
		void Update( Enemy& model, float dt )noexcept;

		void TakeDamage( Enemy& model, float amount )noexcept;
		RectF AABB( Enemy& model )const noexcept;
		float Health( Enemy& model )const noexcept;
		float Damage( Enemy& model )const noexcept;
	};
}