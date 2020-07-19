#pragma once

#include "ChiliMath.h"
#include "Graphics.h"
#include "SpriteCache.h"
#include "Vec2.h"
#include "Weapon.h"
#include "AngleMath.h"
#include <array>
#include <variant>

class World;
class Enemy;

// Scout enemy: Fly down from top, if spots player fires then retreats
class Enemy1
{
public:
	enum class State { Scouting, Turning, Retreating };

public:
	void Update( Enemy& parent, float dt );

public:
	static constexpr auto score_value = 30;
	static constexpr auto speed = 120.f;
	static constexpr auto aabb = RectF{ -30.f, -30.f, 30.f, 30.f };
	static constexpr auto damage = 50.f;
	
private:
	friend class EnemyController;
	friend class EnemyView;

	Weapon m_weapon = { Gun{} };
	State m_state = State::Scouting;
	Radian m_angle = Radian{ Degree{90.f} };
	int m_frame = 0;
};

// Kamekase: Flies in from random position outside of view
//			 toward player, but not chase
class Enemy2
{
public:
	enum State { Drifting, Charging };
public:
	void Update( Enemy& parent, float dt );

public:
	static constexpr auto speed = 120.f;
	static constexpr auto aabb = RectF{ -35.f, -35.f, 35.f, 35.f };
	static constexpr auto damage = 50.f;

private:
	friend class EnemyController;
	friend class EnemyView;

	Radian m_angle = Radian{ Degree{90.f} };
	State m_state = State::Drifting;
};
class Enemy3
{
public:
	void Update( Enemy& parent, float dt );

public:
	static constexpr auto speed = 120.f;
	static constexpr auto aabb = RectF{ -16.f, -16.f, 16.f, 16.f };
	static constexpr auto damage = 50.f;
};
class Enemy4
{
public:
	void Update( Enemy& parent, float dt );

public:
	static constexpr auto speed = 120.f;
	static constexpr auto aabb = RectF{ -16.f, -16.f, 16.f, 16.f };
	static constexpr auto damage = 50.f;
};
class Enemy5
{
public:
	void Update( Enemy& parent, float dt );

public:
	static constexpr auto speed = 120.f;
	static constexpr auto aabb = RectF{ -16.f, -16.f, 16.f, 16.f };
	static constexpr auto damage = 50.f;
};
class Enemy6
{
public:
	void Update( Enemy& parent, float dt ) {}
};

template<typename EnemyType> struct is_enemy {
	static constexpr bool value = std::disjunction_v<
		std::is_same<EnemyType, Enemy1>,
		std::is_same<EnemyType, Enemy2>,
		std::is_same<EnemyType, Enemy3>,
		std::is_same<EnemyType, Enemy4>,
		std::is_same<EnemyType, Enemy5>
	>;
};

template<typename T>
constexpr bool is_enemy_v = is_enemy<T>::value;

class Enemy
{
public:
	void Update( float dt );

public:
	static constexpr int score_value = 10;

	std::variant<Enemy1, Enemy2, Enemy3, Enemy4, Enemy5> variant;
	Vec2 position = { 0.f, -16.f };
	Vec2 velocity = { 0.f, 0.f };
	float health = 100.f;
};