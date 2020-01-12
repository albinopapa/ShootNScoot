#pragma once

#include "EntityController.h"
#include "Rect.h"

namespace sns
{
	class Boss;
	class Boss1;
	class Boss2;
	class Boss3;
	class Boss4;
	class Boss5;
	class Boss6;
	class Boss7;
	class Boss8;
	class Boss9;
	class Boss10;

	class World;

	template<> struct EntityController<Boss>
	{
		static void Update( Boss& model, World& world_model, float dt )noexcept;
		static void TakeDamage( Boss& model, float amount )noexcept;

		static RectF AABB( Boss const& model )noexcept;
		static float Damage( Boss const& model )noexcept;
		static float Health( Boss const& model )noexcept;

	private:
		static void Update( Boss1& model, World& world, Boss& parent, float dt )noexcept;
		static void Update( Boss2& model, World& world, Boss& parent, float dt )noexcept;
		static void Update( Boss3& model, World& world, Boss& parent, float dt )noexcept;
		static void Update( Boss4& model, World& world, Boss& parent, float dt )noexcept;
		static void Update( Boss5& model, World& world, Boss& parent, float dt )noexcept;
		static void Update( Boss6& model, World& world, Boss& parent, float dt )noexcept;
		static void Update( Boss7& model, World& world, Boss& parent, float dt )noexcept;
		static void Update( Boss8& model, World& world, Boss& parent, float dt )noexcept;
		static void Update( Boss9& model, World& world, Boss& parent, float dt )noexcept;
		static void Update( Boss10& model, World& world, Boss& parent, float dt )noexcept;
	};
}
