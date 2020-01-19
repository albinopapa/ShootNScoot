#pragma once

#include "EntityController.h"
#include "Rect.h"

namespace sns
{
	class Boss;
	struct Boss1;
	struct Boss2;
	struct Boss3;
	struct Boss4;
	struct Boss5;
	struct Boss6;
	struct Boss7;
	struct Boss8;
	struct Boss9;
	struct Boss10;

	class World;

	template<> class EntityController<Boss>
	{
	public:
		static void Update( Boss& model, World& world_model, Vec2& hero_position, float dt )noexcept;
		static void TakeDamage( Boss& model, float amount )noexcept;

		static RectF AABB( Boss const& model )noexcept;
		static float Damage( Boss const& model )noexcept;
		static float Health( Boss const& model )noexcept;
		static void Reset( Boss& model )noexcept;

	private:
		static void Update( Boss1& model, World& world, Boss& parent, Vec2 const& hero_position, float dt )noexcept;
		static void Update( Boss2& model, World& world, Boss& parent, Vec2 const& hero_position, float dt )noexcept;
		static void Update( Boss3& model, World& world, Boss& parent, Vec2& hero_position, float dt )noexcept;
		static void Update( Boss4& model, World& world, Boss& parent, Vec2& hero_position, float dt )noexcept;
		static void Update( Boss5& model, World& world, Boss& parent, Vec2& hero_position, float dt )noexcept;
		static void Update( Boss6& model, World& world, Boss& parent, Vec2& hero_position, float dt )noexcept;
		static void Update( Boss7& model, World& world, Boss& parent, Vec2& hero_position, float dt )noexcept;
		static void Update( Boss8& model, World& world, Boss& parent, Vec2& hero_position, float dt )noexcept;
		static void Update( Boss9& model, World& world, Boss& parent, Vec2& hero_position, float dt )noexcept;
		static void Update( Boss10& model, World& world, Boss& parent, Vec2& hero_position, float dt )noexcept;
	};
}
