#pragma once

#include "ChiliMath.h"
#include "EntityController.h"
#include "Graphics.h"
#include "Surface.h"
#include "Utilities.h"
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
		static constexpr auto aabb = RectF{ -16.f, -16.f, 16.f, 16.f };
		static constexpr auto damage = 50.f;
		static constexpr auto waypoints = std::array{
			Vec2{ -aabb.Width(), aabb.Height() * .5f},
			Vec2{ screenRect.Width() -aabb.Width() * .5f, aabb.Height() * .5f },
			Vec2{ screenRect.Width() * .5f, screenRect.Height() + aabb.Height() }
		};
		inline static const Surface	sprite = "Images/Enemy1Ship.png";

	};
	struct Enemy2
	{ 
		static constexpr auto speed = 120.f;
		static constexpr auto aabb = RectF{ -16.f, -16.f, 16.f, 16.f };
		static constexpr auto damage = 50.f;
		static constexpr auto waypoints = std::array{
			Vec2{ -aabb.Width(), aabb.Height() * .5f },
			Vec2{ screenRect.Width() * .5f, screenRect.Height() },
			Vec2{ screenRect.Width() + aabb.Width() / 2.f, -aabb.Height() / 2.f
			}
		};
		inline static const Surface	sprite = "Images/Enemy1Ship.png";
	};
	struct Enemy3 
	{ 
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
		inline static const Surface	sprite = "Images/Enemy1Ship.png";
	};
	struct Enemy4 
	{ 
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
		inline static const Surface	sprite = "Images/Enemy1Ship.png";
	};
	struct Enemy5 
	{ 
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
		inline static const Surface	sprite = "Images/Enemy1Ship.png";
	};

	class Enemy
	{
	public:
		using Controller = EntityController<Enemy>;
		using EnemyType = std::variant<Enemy1, Enemy2, Enemy3, Enemy4, Enemy5>;

	public:
		Enemy( EnemyType const& variant_ )noexcept;
		void Update( float dt );
		
	public:
		static constexpr int score_value = 10;
	private:
		friend struct EntityController<Enemy>;
		Bezier<Vec2> waypoints;
		Vec2 position = { 0.f, -16.f };
		Vec2 velocity = { 0.f, 0.f };
		float health = 100.f;
		float angle = 0.f;
		int waypoint_index = 0;
		EnemyType variant;
	};


}