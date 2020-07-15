#pragma once

#include "Bullet.h"
#include "Enumerations.h"
#include <variant>

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

class Weapon
{
public:
	void Update( float dt )noexcept;
	void Reset()noexcept;

public:
	std::variant<Gun, MachineGun, PlasmaGun, MissileLauncher> variant;
	float fire_timer = 0.f;
	WeaponState state = WeaponState::Idle;
};
