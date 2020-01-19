#pragma once

#include "ChiliMath.h"
#include "EntityController.h"
#include "RectController.h"
#include "Surface.h"
#include "SurfaceController.h"
#include "Utilities.h"
#include "Vec2.h"
#include <variant>
#include <vector>

namespace sns
{
	class World;

	struct Enemy1
	{ 
		static constexpr auto score_value = 30;
		static constexpr auto speed = 120.f;
		static constexpr auto aabb = RectF{ -16.f, -16.f, 16.f, 16.f };
		static constexpr auto damage = 50.f;
		static std::vector<Vec2> waypoints;
		inline static const Surface	sprite = SurfaceController::CreateSurface( "Images/Enemy1Ship.png" );

	};
	struct Enemy2
	{ 
		static constexpr auto speed = 120.f;
		static constexpr auto aabb = RectF{ -16.f, -16.f, 16.f, 16.f };
		static constexpr auto damage = 50.f;
		static std::vector<Vec2> waypoints;
		inline static const Surface	sprite = SurfaceController::CreateSurface( "Images/Enemy1Ship.png" );
	};
	struct Enemy3 
	{ 
		static constexpr auto speed = 120.f;
		static constexpr auto aabb = RectF{ -16.f, -16.f, 16.f, 16.f };
		static constexpr auto damage = 50.f;
		static std::vector<Vec2> waypoints;
		inline static const Surface	sprite = SurfaceController::CreateSurface( "Images/Enemy1Ship.png" );
	};
	struct Enemy4 
	{ 
		static constexpr auto speed = 120.f;
		static constexpr auto aabb = RectF{ -16.f, -16.f, 16.f, 16.f };
		static constexpr auto damage = 50.f;
		static std::vector<Vec2> waypoints;
		inline static const Surface	sprite = SurfaceController::CreateSurface( "Images/Enemy1Ship.png" );
	};
	struct Enemy5 
	{ 
		static constexpr auto speed = 120.f;
		static constexpr auto aabb = RectF{ -16.f, -16.f, 16.f, 16.f };
		static constexpr auto damage = 50.f;
		static std::vector<Vec2> waypoints;
		inline static const Surface	sprite = SurfaceController::CreateSurface( "Images/Enemy1Ship.png" );
	};

	class Enemy
	{
	public:
		using EnemyType = std::variant<Enemy1, Enemy2, Enemy3, Enemy4, Enemy5>;

	public:
		Enemy( std::vector<Vec2> waypoints, EnemyType const& variant_ )noexcept;
		
	public:
		static constexpr int score_value = 10;

	private:
		friend class EntityController<Enemy>;
		friend class EnemyView;

		Bezier<Vec2> waypoints;
		Vec2 position = { 0.f, -16.f };
		Vec2 velocity = { 0.f, 0.f };
		float health = 100.f;
		float angle = 0.f;
		int waypoint_index = 0;
		EnemyType variant;
	};


}