#pragma once

#include "Bullet.h"
#include <variant>

namespace sns
{
	struct World;

	struct Gun
	{
		using ammo_type = Bullet;
		static constexpr float fire_delay = 15.f / 60.f;
	};
	struct MachineGun
	{
		using ammo_type = Bullet;
		static constexpr float fire_delay = 7.5f / 60.f;
	};
	struct PlasmaGun
	{
		using ammo_type = PlasmaBall;
		static constexpr float fire_delay = 60.f / 60.f;
	};
	struct MissileLauncher
	{
		using ammo_type = Missile;
		static constexpr float fire_delay = 30.f / 60.f;
	};
	struct Weapon
	{
	public:
		void Update( float dt )noexcept;
		bool CanFire()const noexcept;
		void Fire( Vec2 const& position, Vec2 const& direction, World& world, Ammo::Owner ammo_owner = Ammo::Owner::Hero )noexcept;
		void Reset()noexcept;

	public:
		enum class State { Idle, Recharge };

	public:
		std::variant<Gun, MachineGun, PlasmaGun, MissileLauncher> variant;
		float fire_timer = 0.f;
		State state = State::Idle;
	};
}