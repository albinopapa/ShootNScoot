#pragma once

#include "Enemies.h"
#include "Rect.h"
#include "World.h"

class EnemyController
{
public:
	void Update( Enemy& model, World& world, float dt )noexcept;

	void TakeDamage( Enemy& model, float amount )noexcept;
	RectF AABB( Enemy& model )const noexcept;
	float Health( Enemy& model )const noexcept;
	float Damage( Enemy& model )const noexcept;

private:
	void Update( Enemy& parent, Enemy1& enemy, World& world, float dt )noexcept;
	void Update( Enemy& parent, Enemy2& enemy, World& world, float dt )noexcept;
	void Update( Enemy& parent, Enemy3& enemy, World& world, float dt )noexcept;
	void Update( Enemy& parent, Enemy4& enemy, World& world, float dt )noexcept;
	void Update( Enemy& parent, Enemy5& enemy, World& world, float dt )noexcept;

};
