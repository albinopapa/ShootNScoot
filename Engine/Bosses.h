#pragma once

#include "Enumerations.h"
#include "Graphics.h"		// For screenRect
#include "Shield.h"
#include "Surface.h"
#include "Weapon.h"
#include <variant>

namespace sns
{
	struct Boss1
	{
	public:
		void Update( Vec2& position, Vec2& direction, float dt );

		static constexpr auto aabb = RectF{ -16.f, -16.f, 16.f, 16.f };
		static constexpr auto damage = 50.f;
		static constexpr auto regen_delay = 3.f;
		static constexpr auto max_missiles = 10;
		static constexpr auto max_health = 200.f;
		static constexpr auto speed = 160.f;
		inline static const Surface sprite = { "Images/Enemy1Ship.png" };

		Shield shield;
		Weapon weapon = { MissileLauncher{} };
		Boss1State state = Boss1State::Idle;
		float regen_timer = regen_delay;
		int missile_count = 0;
	};

	struct Boss2
	{
	public:
		enum class State { Idle, Signaling, Ramming, Recharging };

	public:
		void Update( Vec2& position, Vec2& direction, float dt )noexcept;

	public:
		static constexpr auto aabb = RectF{ -16.f, -16.f, 16.f, 16.f };
		static constexpr auto damage = 50.f;
		static constexpr auto speed = 720.f;
		static constexpr auto signal_delay = .25f;
		static constexpr auto cool_down_delay = 3.f;
		inline static const Surface sprite = { "Images/Boss2Ship.png" };

		Vec2 waypoint;
		State state = State::Idle;
		float cool_down_timer = 0.f;
		float signal_timer = signal_delay;
	};

	struct Boss
	{
	public:
		using BossType = std::variant<Boss1, Boss2>;

	public:
		Boss( BossType type )noexcept;
		void Update( float dt );
		void Reset()noexcept;

	public:
		BossType variant;
		Vec2 position = { screenRect.Center().x, -32.f };
		Vec2 direction = { 0.f, 1.f };
		float angle = 0.f;
		float health = 0.f;
	};
}
