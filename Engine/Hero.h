#pragma once

#include "Bullet.h"
#include "EntityController.h"
#include "Rect.h"
#include "Shield.h"
#include "SpriteEffect.h"
#include "Surface.h"
#include "Vec2.h"
#include "Weapon.h"

namespace sns
{
	class Hero
	{
	public:
		using Controller = EntityController<Hero>;
	public:
		void Update( float dt );
		void Reset()noexcept;

	private:
		friend struct EntityController<Hero>;
		Surface	sprite = "Images/HeroShip.png";
		Shield shield;
		Weapon weapon = Weapon{ Gun{} };
		Vec2 position = { 400.f, 300.f };
		Vec2 velocity = { 0.f, 0.f };
		float health = 100.f;
		static constexpr auto aabb		= RectF{ -16.f, -16.f, 16.f, 16.f };
		static constexpr auto max_speed = 120.f;
		static constexpr auto damage	= 20.f;
	};

}
