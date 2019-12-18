#pragma once

#include "ChiliWin.h"
#include "Graphics.h"
#include "Weapon.h"
#include "Keyboard.h"
#include "Rect.h"
#include "Shield.h"
#include "SpriteEffect.h"
#include <algorithm>

namespace sns
{
	struct World;

	struct Hero
	{
	public:
		Hero()noexcept;
		void Update( Keyboard& kbd, float dt, World& world );
		void TakeDamage( float amount )noexcept;
		void Draw( Surface const& sprite, Graphics& gfx )const noexcept;
		void Reset()noexcept;
		RectF AABB()const noexcept;

	public:
		static constexpr auto aabb		= RectF{ -16.f, -16.f, 16.f, 16.f };
		static constexpr auto max_speed = 120.f;
		static constexpr auto damage	= 20.f;

		Shield shield;
		Weapon weapon;
		Vec2 position, velocity;
		float health = 100.f;
	};

}
