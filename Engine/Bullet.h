#pragma once

#include "Colors.h"
#include "EntityController.h"
#include "Surface.h"
#include "Vec2.h"
#include <variant>

namespace sns
{
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
		enum class Owner { Hero, Enemy };

	public:
		using Controller = EntityController<Ammo>;
		using AmmoType = std::variant<Bullet, PlasmaBall, Missile>;

	public:
		Ammo( Vec2 const& position_, Vec2 const& direction_, Owner owner_, AmmoType type );
		void Update( float delta_time )noexcept;

	private:
		friend struct EntityController<Ammo>;
		Vec2 position;
		Vec2 velocity;
		float energy = 0.f;
		Owner owner = Owner::Hero;
		AmmoType variant;
		bool isAlive = true;
	};
}

