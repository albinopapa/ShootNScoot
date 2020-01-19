#include "ChiliWin.h"
#include "Hero.h"
#include "HeroController.h"
#include "KbdController.h"
#include "RectController.h"
#include "ShieldController.h"
#include "Vec2Controller.h"
#include "WeaponController.h"
#include "World.h"

namespace sns
{
	void EntityController<Hero>::Update(
		Hero& model,
		World& world,
		Keyboard const& kbd,
		float dt ) noexcept
	{
		UpdateVelocity( model, kbd );
		ChangeWeapon( model, kbd );
		
		model.position += ( model.velocity * ( Hero::max_speed * dt ) );
		ShieldController::Update( model.shield, model.position, dt );

		const auto heroRect = AABB( model );

		if( !RectController::IsContainedBy( heroRect, screen_rect ) )
		{
			model.position.x = std::clamp(
				model.position.x,
				screen_rect.left + Hero::aabb.right,
				screen_rect.right + Hero::aabb.left
			);
			model.position.y = std::clamp(
				model.position.y,
				screen_rect.top + Hero::aabb.bottom,
				screen_rect.bottom + Hero::aabb.top
			);
		}

		WeaponController::Update( model.weapon, dt );

		if( KbdController::KeyIsPressed( kbd, VK_CONTROL ) &&
			WeaponController::CanFire( model.weapon ) )
		{
			WeaponController::Fire(
				model.weapon,
				model.position, 
				Vec2{ 0.f, -1.f },
				world,
				Ammo::Owner::Hero
			);
		}
	}
	
	void EntityController<Hero>::TakeDamage( Hero& model, float amount )noexcept
	{
		if( ShieldController::Health( model.shield ) > 0.f )
			ShieldController::TakeDamage( model.shield, amount );
		else
			model.health -= amount;

		model.health = std::max( model.health, 0.f );
	}

	float EntityController<Hero>::Damage( Hero const& model )noexcept
	{
		return Hero::damage;
	}

	RectF EntityController<Hero>::AABB( Hero const& model )noexcept
	{
		if( ShieldController::Health( model.shield ) > 0.f )
			return ShieldController::AABB( model.shield, model.position );
		else
			return Hero::aabb + model.position;
	}

	float EntityController<Hero>::Health( Hero const & model ) noexcept
	{
		return model.health;
	}

	Vec2 const & EntityController<Hero>::Position( Hero const & model ) noexcept
	{
		return model.position;
	}
	
	Vec2& EntityController<Hero>::Position( Hero& model )noexcept
	{
		return model.position;
	}

	void EntityController<Hero>::Reset( Hero & model ) noexcept
	{
		WeaponController::Reset( model.weapon );
		ShieldController::Reset( model.shield );
		model.health = 100.f;
		model.velocity = { 0.f, 0.f };
		model.position = { 0.f, 0.f };
	}

	void EntityController<Hero>::UpdateVelocity( Hero& model, Keyboard const & kbd ) noexcept
	{
		Vec2 direction = { 0.f, 0.f };
		if( KbdController::KeyIsPressed( kbd, VK_UP ) )
		{
			direction.y = -1.f;
		}
		else if( KbdController::KeyIsPressed( kbd, VK_DOWN ) )
		{
			direction.y = 1.f;
		}

		if( KbdController::KeyIsPressed( kbd, VK_LEFT ) )
		{
			direction.x = -1.f;
		}
		else if( KbdController::KeyIsPressed( kbd, VK_RIGHT ) )
		{
			direction.x = 1.f;
		}

		model.velocity = Vec2Controller::Normalize( direction );
	}

	void EntityController<Hero>::ChangeWeapon( Hero& model, Keyboard const & kbd ) noexcept
	{
		if( KbdController::KeyIsPressed( kbd, '1' ) )
		{
			WeaponController::SwitchWeapon<Gun>( model.weapon );
		}
		else if( KbdController::KeyIsPressed( kbd, '2' ) )
		{
			WeaponController::SwitchWeapon<MachineGun>( model.weapon );
		}
		else if( KbdController::KeyIsPressed( kbd, '3' ) )
		{
			WeaponController::SwitchWeapon<PlasmaGun>( model.weapon );
		}
	}
}
