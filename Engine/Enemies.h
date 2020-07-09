#pragma once

#include "ChiliMath.h"
#include "Graphics.h"
#include "SpriteEffect.h"
#include "Vec2.h"
#include <array>
#include <variant>

namespace sns
{
	class World;

	struct Enemy1
	{ 
		static constexpr auto score_value = 30;
		static constexpr auto speed = 120.f;
		static constexpr auto aabb = RectF{ -5.f,-10.f,5.0f,10.0f};
		static constexpr auto damage = 50.f;
		static constexpr auto waypoints = std::array{
			Vec2{ -aabb.Width(), aabb.Height() * .5f},
			Vec2{ screenRect.Width() -aabb.Width() * .5f, aabb.Height() * .5f },
			Vec2{ screenRect.Width() * .5f, screenRect.Height()/2 + aabb.Height() }
		};
	};
	struct Enemy2
	{ 
		static constexpr auto speed = 120.f;
		static constexpr auto aabb = RectF{ -5.f,-10.f,5.0f,10.0f};
		static constexpr auto damage = 50.f;
		static constexpr auto waypoints = std::array{
				Vec2{ -aabb.Width(), aabb.Height() * .5f},
			Vec2{ screenRect.Width() - aabb.Width() * .5f, aabb.Height() * .5f },
			Vec2{ screenRect.Width() * .5f, screenRect.Height()/2 + aabb.Height() }
		};
	};
	struct Enemy3 
	{ 
		static constexpr auto speed = 120.f;
		static constexpr auto aabb = RectF{ -5.f,-10.f,5.0f,10.0f};
		static constexpr auto damage = 50.f;
		static constexpr auto waypoints = std::array{
			Vec2{ -aabb.Width(), aabb.Height() * .5f},
			Vec2{ screenRect.Width() - aabb.Width() * .5f, aabb.Height() * .5f },
			Vec2{ screenRect.Width() * .5f, screenRect.Height()/2 + aabb.Height() }
		};
	};
	struct Enemy4 
	{ 
		static constexpr auto speed = 120.f;
		static constexpr auto aabb = RectF{ -5.f,-10.f,5.0f,10.0f};
		static constexpr auto damage = 50.f;
		static constexpr auto waypoints = std::array{
			Vec2{ -aabb.Width(), aabb.Height() * .5f},
			Vec2{ screenRect.Width() - aabb.Width() * .5f, aabb.Height() * .5f },
			Vec2{ screenRect.Width() * .5f, screenRect.Height()/2 + aabb.Height() }
		};
	};
	struct Enemy5 
	{ 
		static constexpr auto speed = 120.f;
		static constexpr auto aabb = RectF{ 0.f, 0.f, 10.f, 20.f };
		static constexpr auto damage = 50.f;
		static constexpr auto waypoints = std::array{
			Vec2{ -aabb.Width(), aabb.Height() * .5f},
			Vec2{ screenRect.Width() - aabb.Width() * .5f, aabb.Height() * .5f },
			Vec2{ screenRect.Width() * .5f, screenRect.Height() + aabb.Height() }
		};
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
		Vec2 position = { 0.f, -10.f };
		Vec2 velocity = { 0.f, 0.f };
		float health = 100.f;
		int waypoint_index = 0;
	};


}