#include "WeaponController.h"
#include "Weapon.h"
#include "World.h"


	void WeaponController::Update( Weapon& model, float dt )
	{
		if( model.state == WeaponState::Recharge )
		{
			if( model.fire_timer <= 0.f )
			{
				model.state = WeaponState::Idle;
			}
		}
	}
	bool WeaponController::CanFire( Weapon& model ) const noexcept
	{
		return model.state == WeaponState::Idle;
	}
	void WeaponController::Fire( 
		Weapon& model,
		Vec2 const & position, 
		Vec2 const & direction, 
		World& world, 
		AmmoOwner ammo_owner )
	{
		if( model.state == WeaponState::Idle )
		{
			std::visit( [ & ]( auto& weapon ) {
				using type = std::decay_t<decltype( weapon )>;
				using ammo_type = type::ammo_type;
				world.SpawnAmmo( Ammo{ position, direction, ammo_type::max_energy, ammo_owner, ammo_type{} } );

				model.state = WeaponState::Recharge;

				model.fire_timer = type::fire_delay;
			}, model.variant );
		}
	}

