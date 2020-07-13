#pragma once

#include "Colors.h"
#include "Enumerations.h"
#include "Surface.h"
#include "Vec2.h"
#include <variant>

	struct Bullet
	{
		static constexpr auto aabb			= RectF{ -1.f, -2.f, 1.f, 2.f };
		static constexpr auto color			= Colors::White;
		static constexpr auto speed			= 360.f;
		static constexpr auto damage		= 25.f;
		static constexpr auto max_energy	= 1.f;
		static const Surface sprite;
	};
	struct PlasmaBall
	{
		static constexpr auto radius		= 16.f;
		static constexpr auto aabb			= RectF{ -radius, -radius, radius, radius };
		static constexpr auto color			= Colors::Blue;
		static constexpr auto speed			= 360.f;
		static constexpr auto damage		= 50.f;
		static constexpr auto max_energy	= 100.f;
		static const Surface sprite;
	};
	struct Missile
	{
		static constexpr auto aabb = RectF{ -4.f,-8.f, 4.f, 8.f };
		static constexpr auto color = Colors::Red;
		static constexpr auto speed = 360.f;
		static constexpr auto damage = 50.f;
		static constexpr auto max_energy = 20.f;
		static const Surface sprite;
	};

	class Ammo
	{
	public:
		void Update( float delta_time )noexcept;

	public:
		Vec2 position;
		Vec2 velocity;
		float energy = 0.f;
		AmmoOwner owner = AmmoOwner::Hero;
		std::variant<Bullet, PlasmaBall, Missile> variant;
		bool isAlive = true;
		
	};


