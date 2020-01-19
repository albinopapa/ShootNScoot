#pragma once

#include "EntityController.h"
#include "Rect.h"
#include "RectController.h"
#include "Settings.h"
#include "Shield.h"
#include "Surface.h"
#include "SurfaceController.h"
#include "Vec2.h"
#include "Weapon.h"

namespace sns
{
	class Hero
	{
	private:
		friend class EntityController<Hero>;
		friend class HeroView;

		Surface	sprite = SurfaceController::CreateSurface( "Images/HeroShip.png" );
		Shield shield;
		Weapon weapon = Weapon{ Gun{} };
		Vec2 position = RectController::Center( world_rect );
		Vec2 velocity = { 0.f, 0.f };
		float health = 100.f;
		static constexpr auto aabb		= RectF{ -16.f, -16.f, 16.f, 16.f };
		static constexpr auto max_speed = 120.f;
		static constexpr auto damage	= 20.f;
	};

}
