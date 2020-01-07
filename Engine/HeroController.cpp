#include "HeroController.h"
#include "Hero.h"
#include "World.h"
#include "ShieldController.h"
#include "WeaponController.h"

namespace sns
{
	void HeroController::Update( 
		Hero& model,
		World& world,
		Keyboard const& kbd,
		float dt ) noexcept
	{
		UpdateVelocity( model, kbd );
		ChangeWeapon( model, kbd );
		
		ShieldController::Update( model.shield, model.position, dt );

		const auto heroRect = AABB( model );

		if( !heroRect.IsContainedBy( screenRect ) )
		{
			model.position.x = std::clamp(
				model.position.x,
				screenRect.left + Hero::aabb.right,
				screenRect.right + Hero::aabb.left
			);
			model.position.y = std::clamp(
				model.position.y,
				screenRect.top + Hero::aabb.bottom,
				screenRect.bottom + Hero::aabb.top
			);
		}

		WeaponController::Update( model.weapon, dt );

		if( kbd.KeyIsPressed( VK_CONTROL ) && WeaponController::CanFire( model.weapon ) )
		{
			WeaponController::Fire(
				model.weapon,
				model.position, 
				Vec2{ 0.f, -1.f },
				world,
				AmmoOwner::Hero
			);
		}
	}
	
	
	void HeroController::TakeDamage( Hero& model, float amount )noexcept
	{
		if( model.shield.Health() > 0.f )
			ShieldController::TakeDamage( model.shield, amount );
		else
			model.health -= amount;

		model.health = std::max( model.health, 0.f );
	}

	float HeroController::Damage( Hero const& model )noexcept
	{
		return Hero::damage;
	}

	RectF HeroController::AABB( Hero const& model )noexcept
	{
		return Hero::aabb + model.position;
	}

	Shield const& HeroController::GetShield( Hero const& model )noexcept
	{
		return model.shield;
	}

	float HeroController::Health( Hero const & model ) noexcept
	{
		return model.health;
	}

	Vec2 const & HeroController::Position( Hero const & model ) noexcept
	{
		return model.position;
	}
	
	Shield& HeroController::GetShield( Hero& model ) noexcept
	{
		return model.shield;
	}

	void HeroController::UpdateVelocity( Hero& model, Keyboard const & kbd ) noexcept
	{
		Vec2 direction = { 0.f, 0.f };
		if( kbd.KeyIsPressed( VK_UP ) )
		{
			direction.y = -1.f;
		}
		else if( kbd.KeyIsPressed( VK_DOWN ) )
		{
			direction.y = 1.f;
		}

		if( kbd.KeyIsPressed( VK_LEFT ) )
		{
			direction.x = -1.f;
		}
		else if( kbd.KeyIsPressed( VK_RIGHT ) )
		{
			direction.x = 1.f;
		}

		model.velocity = direction.Normalize();
	}

	void HeroController::ChangeWeapon( Hero& model, Keyboard const & kbd ) noexcept
	{
		if( kbd.KeyIsPressed( '1' ) )
		{
			if( !std::holds_alternative<Gun>( model.weapon.variant ) )
				model.weapon.variant = Gun{};
		}
		else if( kbd.KeyIsPressed( '2' ) )
		{
			if( !std::holds_alternative<MachineGun>( model.weapon.variant ) )
				model.weapon.variant = MachineGun{};
		}
		else if( kbd.KeyIsPressed( '3' ) )
		{
			if( !std::holds_alternative<PlasmaGun>( model.weapon.variant ) )
				model.weapon.variant = PlasmaGun{};
		}
	}
}
