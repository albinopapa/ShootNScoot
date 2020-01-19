#pragma once

#include "EntityController.h"
#include "Rect.h"
#include "RectController.h"
#include "Settings.h"
#include "Shield.h"
#include "Surface.h"
#include "SurfaceController.h"
#include "Weapon.h"
#include <variant>

namespace sns
{
	struct Boss1
	{
	public:
		enum class State { Idle, Attack, Regen };

	public:
		static constexpr auto aabb = RectF{ -16.f, -16.f, 16.f, 16.f };
		static constexpr auto damage = 50.f;
		static constexpr auto regen_delay = 3.f;
		static constexpr auto max_missiles = 10;
		static constexpr auto max_health = 200.f;
		static constexpr auto speed = 160.f;
		inline static const Surface sprite = SurfaceController::CreateSurface( "Images/Enemy1Ship.png" );

		Shield shield;
		Weapon weapon = { MissileLauncher{} };
		State state = State::Idle;
		float regen_timer = regen_delay;
		int missile_count = 0;
	};

	struct Boss2
	{
	public:
		enum class State { Idle, Signaling, Ramming, Recharging };

	public:
		static constexpr auto aabb = RectF{ -16.f, -16.f, 16.f, 16.f };
		static constexpr auto damage = 50.f;
		static constexpr auto speed = 720.f;
		static constexpr auto max_health = 200.f;
		static constexpr auto signal_delay = .25f;
		static constexpr auto cool_down_delay = 3.f;
		inline static const Surface sprite = SurfaceController::CreateSurface( "Images/Boss2Ship.png"  );

		Vec2 waypoint;
		State state = State::Idle;
		float cool_down_timer = 0.f;
		float signal_timer = signal_delay;
	};

	struct Boss3
	{
	public:
		enum class State { Idle, Attack, Regen };

	public:
		static constexpr auto aabb = RectF{ -16.f, -16.f, 16.f, 16.f };
		static constexpr auto damage = 50.f;
		static constexpr auto regen_delay = 3.f;
		static constexpr auto max_missiles = 10;
		static constexpr auto max_health = 200.f;
		static constexpr auto speed = 160.f;
		inline static const Surface sprite = SurfaceController::CreateSurface( "Images/Enemy1Ship.png" );

		Shield shield;
		Weapon weapon = { MissileLauncher{} };
		State state = State::Idle;
		float regen_timer = regen_delay;
		int missile_count = 0;
	};

	struct Boss4
	{
	public:
		enum class State { Idle, Signaling, Ramming, Recharging };

	public:
		static constexpr auto aabb = RectF{ -16.f, -16.f, 16.f, 16.f };
		static constexpr auto damage = 50.f;
		static constexpr auto speed = 720.f;
		static constexpr auto max_health = 200.f;
		static constexpr auto signal_delay = .25f;
		static constexpr auto cool_down_delay = 3.f;
		inline static const Surface sprite = SurfaceController::CreateSurface( "Images/Boss2Ship.png" );

		Vec2 waypoint;
		State state = State::Idle;
		float cool_down_timer = 0.f;
		float signal_timer = signal_delay;
	};

	struct Boss5
	{
	public:
		enum class State { Idle, Attack, Regen };

	public:
		static constexpr auto aabb = RectF{ -16.f, -16.f, 16.f, 16.f };
		static constexpr auto damage = 50.f;
		static constexpr auto regen_delay = 3.f;
		static constexpr auto max_missiles = 10;
		static constexpr auto max_health = 200.f;
		static constexpr auto speed = 160.f;
		inline static const Surface sprite = SurfaceController::CreateSurface( "Images/Enemy1Ship.png" );

		Shield shield;
		Weapon weapon = { MissileLauncher{} };
		State state = State::Idle;
		float regen_timer = regen_delay;
		int missile_count = 0;
	};

	struct Boss6
	{
	public:
		enum class State { Idle, Signaling, Ramming, Recharging };

	public:
		static constexpr auto aabb = RectF{ -16.f, -16.f, 16.f, 16.f };
		static constexpr auto damage = 50.f;
		static constexpr auto speed = 720.f;
		static constexpr auto max_health = 200.f;
		static constexpr auto signal_delay = .25f;
		static constexpr auto cool_down_delay = 3.f;
		inline static const Surface sprite = SurfaceController::CreateSurface( "Images/Boss2Ship.png" );

		Vec2 waypoint;
		State state = State::Idle;
		float cool_down_timer = 0.f;
		float signal_timer = signal_delay;
	};

	struct Boss7
	{
	public:
		enum class State { Idle, Attack, Regen };

	public:
		static constexpr auto aabb = RectF{ -16.f, -16.f, 16.f, 16.f };
		static constexpr auto damage = 50.f;
		static constexpr auto regen_delay = 3.f;
		static constexpr auto max_missiles = 10;
		static constexpr auto max_health = 200.f;
		static constexpr auto speed = 160.f;
		inline static const Surface sprite = SurfaceController::CreateSurface( "Images/Enemy1Ship.png" );

		Shield shield;
		Weapon weapon = { MissileLauncher{} };
		State state = State::Idle;
		float regen_timer = regen_delay;
		int missile_count = 0;
	};

	struct Boss8
	{
	public:
		enum class State { Idle, Signaling, Ramming, Recharging };

	public:
		static constexpr auto aabb = RectF{ -16.f, -16.f, 16.f, 16.f };
		static constexpr auto damage = 50.f;
		static constexpr auto speed = 720.f;
		static constexpr auto max_health = 200.f;
		static constexpr auto signal_delay = .25f;
		static constexpr auto cool_down_delay = 3.f;
		inline static const Surface sprite = SurfaceController::CreateSurface( "Images/Boss2Ship.png" );

		Vec2 waypoint;
		State state = State::Idle;
		float cool_down_timer = 0.f;
		float signal_timer = signal_delay;
	};

	struct Boss9
	{
	public:
		enum class State { Idle, Attack, Regen };

	public:
		static constexpr auto aabb = RectF{ -16.f, -16.f, 16.f, 16.f };
		static constexpr auto damage = 50.f;
		static constexpr auto regen_delay = 3.f;
		static constexpr auto max_missiles = 10;
		static constexpr auto max_health = 200.f;
		static constexpr auto speed = 160.f;
		inline static const Surface sprite = SurfaceController::CreateSurface( "Images/Enemy1Ship.png" );

		Shield shield;
		Weapon weapon = { MissileLauncher{} };
		State state = State::Idle;
		float regen_timer = regen_delay;
		int missile_count = 0;
	};

	struct Boss10
	{
	public:
		enum class State { Idle, Signaling, Ramming, Recharging };

	public:
		static constexpr auto aabb = RectF{ -16.f, -16.f, 16.f, 16.f };
		static constexpr auto damage = 50.f;
		static constexpr auto speed = 720.f;
		static constexpr auto max_health = 200.f;
		static constexpr auto signal_delay = .25f;
		static constexpr auto cool_down_delay = 3.f;
		inline static const Surface sprite = SurfaceController::CreateSurface( "Images/Boss2Ship.png" );

		Vec2 waypoint;
		State state = State::Idle;
		float cool_down_timer = 0.f;
		float signal_timer = signal_delay;
	};

	class Boss
	{
	public:
		using BossType = std::variant<
			Boss1, 
			Boss2,
			Boss3,
			Boss4,
			Boss5,
			Boss6,
			Boss7,
			Boss8,
			Boss9,
			Boss10
		>;

	public:
		Boss( BossType type )noexcept;

	private:
		friend class EntityController<Boss>;
		friend class BossView;

		BossType variant;
		Vec2 position = { RectController::Center( world_rect ).x, world_rect.top };
		Vec2 direction = { 0.f, 1.f };
		float angle = 0.f;
		float health = 0.f;
	};
}
