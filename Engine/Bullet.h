#pragma once

#include "Colors.h"
#include "Graphics.h"
#include "Vec2.h"
#include <variant>

namespace sns
{
	struct Bullet
	{
		static void DrawEffect( float x, float y, Vec2 const& position, Graphics& gfx )noexcept;

		static constexpr auto aabb			= RectF{ -1.f, -2.f, 1.f, 2.f };
		static constexpr auto color			= Colors::White;
		static constexpr auto speed			= 360.f;
		static constexpr auto damage		= 25.f;
		static constexpr auto max_energy	= 1.f;
	};
	struct PlasmaBall
	{
		static void DrawEffect( float x, float y, Vec2 const& position, Graphics& gfx )noexcept;
		static constexpr auto radius		= 16.f;
		static constexpr auto aabb			= RectF{ -radius, -radius, radius, radius };
		static constexpr auto color			= Colors::Blue;
		static constexpr auto speed			= 360.f;
		static constexpr auto damage		= 50.f;
		static constexpr auto max_energy	= 100.f;
	};
	struct Missile
	{
		static void DrawEffect( float x, float y, Vec2 const& position, Graphics& gfx )noexcept;
		static constexpr auto aabb = RectF{ -4.f,-8.f, 4.f, 8.f };
		static constexpr auto color = Colors::Red;
		static constexpr auto speed = 360.f;
		static constexpr auto damage = 50.f;
		static constexpr auto max_energy = 20.f;
	};
	struct Ammo
	{
		void Update( float delta_time )noexcept;
		void TakeDamage( float amount )noexcept;
		float Damage()const noexcept;
		RectF AABB()const noexcept;
		void Draw( Graphics& gfx )const noexcept;

		enum class Owner { Hero, Enemy };

		Vec2 position, velocity;
		float energy = 0.f;
		Owner owner = Owner::Hero;
		std::variant<Bullet, PlasmaBall, Missile> variant;
		bool isAlive = true;
		
	};
}

