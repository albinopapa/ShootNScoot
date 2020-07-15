#pragma once

#include "ChiliMath.h"
#include "Graphics.h"
#include "SpriteEffect.h"
#include "Vec2.h"
#include "Weapon.h"

#include <array>
#include <variant>

class World;
class Enemy;

// Scout enemy: Fly down from top, if spots player fires then retreats
class Enemy1
{
public:
	enum class State { Scouting, Retreating };

public:
	void Update( Enemy& parent, float dt );

public:
	static constexpr auto score_value = 30;
	static constexpr auto speed = 120.f;
	static constexpr auto aabb = RectF{ -30.f, -30.f, 30.f, 30.f };
	static constexpr auto damage = 50.f;
	static std::vector<Surface> frames;

private:
	friend class EnemyController;

	Weapon m_weapon = { Gun{} };
	State m_state = State::Scouting;
	int m_frame = 0;
	bool m_hero_spotted = false;
};

// Kamekase: Flies in from random position outside of view
//			 toward player, but not chase
class Enemy2
{
public:
	void Update( Enemy& parent, float dt );

public:
	static constexpr auto speed = 120.f;
	static constexpr auto aabb = RectF{ -16.f, -16.f, 16.f, 16.f };
	static constexpr auto damage = 50.f;
	static constexpr auto waypoints = std::array{
		Vec2{ -aabb.Width(), aabb.Height() * .5f },
		Vec2{ screenRect.Width() * .5f, screenRect.Height() },
		Vec2{ screenRect.Width() + aabb.Width() / 2.f, -aabb.Height() / 2.f
		}
	};

};
class Enemy3
{
public:
	void Update( Enemy& parent, float dt );

public:
	static constexpr auto speed = 120.f;
	static constexpr auto aabb = RectF{ -16.f, -16.f, 16.f, 16.f };
	static constexpr auto damage = 50.f;
	static constexpr auto waypoints = std::array{
		Vec2{ -aabb.Width(), aabb.Height() * .5f },
		Vec2{
			screenRect.Width() + aabb.Width() / 2.f,
			screenRect.Height() + aabb.Height() / 2.f
		}
	};
};
class Enemy4
{
public:
	void Update( Enemy& parent, float dt );

public:
	static constexpr auto speed = 120.f;
	static constexpr auto aabb = RectF{ -16.f, -16.f, 16.f, 16.f };
	static constexpr auto damage = 50.f;
	static constexpr auto waypoints = std::array{
		Vec2{ screenRect.Width() / 2.f + 50.f,   0.f },
		Vec2{ screenRect.Width() / 2.f - 50.f, 100.f },
		Vec2{ screenRect.Width() / 2.f + 50.f, 200.f },
		Vec2{ screenRect.Width() / 2.f - 50.f, 300.f },
		Vec2{ screenRect.Width() / 2.f + 50.f, 400.f },
		Vec2{ screenRect.Width() / 2.f - 50.f, 500.f },
		Vec2{ screenRect.Width() / 2.f + 50.f, 600.f }
	};
};
class Enemy5
{
public:
	void Update( Enemy& parent, float dt );

public:
	static constexpr auto speed = 120.f;
	static constexpr auto aabb = RectF{ -16.f, -16.f, 16.f, 16.f };
	static constexpr auto damage = 50.f;
	static constexpr auto waypoints = std::array{
		Vec2{ screenRect.Width() / 2.f, 0.f },
		Vec2{ aabb.Width() / 2.f,	screenRect.Height() / 2.f },
		Vec2{ screenRect.Width() / 2.f, screenRect.Height() },
		Vec2{ screenRect.Width(), screenRect.Height() / 2.f },
		Vec2{ screenRect.Width() / 2.f + aabb.Width() / 2.f, -aabb.Height() / 2.f }
	};
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
	int waypoint_index = 0;
};