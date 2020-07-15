#pragma once

#include "ChiliWin.h"
#include "Graphics.h"
#include "Weapon.h"
#include "Keyboard.h"
#include "Rect.h"
#include "Shield.h"
#include "SpriteEffect.h"
#include <algorithm>

class Hero
{
public:
	void Update( float dt );
	void Reset()noexcept;

public:
	static constexpr auto aabb = RectF{ -16.f, -16.f, 16.f, 16.f };
	static constexpr auto max_speed = 120.f;
	static constexpr auto damage = 20.f;

	Shield shield;
	Weapon weapon = Weapon{ Gun{} };
	Vec2 position = { 400.f, 300.f };
	Vec2 velocity = { 0.f, 0.f };
	float health = 100.f;
};
