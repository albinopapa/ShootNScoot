#include "WeaponController.h"
#include "Bullet.h"
#include "Weapon.h"
#include "World.h"

namespace sns
{
	void WeaponController::Update( Weapon& model, float dt )noexcept
	{
		if( model.state == WeaponState::Recharge )
		{
			if( model.fire_timer <= 0.f )
			{
				model.state = WeaponState::Idle;
			}
		}
	}
	bool WeaponController::CanFire( Weapon const& model )noexcept
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
				world.SpawnAmmo( Ammo{ position, direction, ammo_owner, type::ammo_type{} } );

				model.state = WeaponState::Recharge;

				model.fire_timer = type::fire_delay;
			}, model.variant );
		}
	}
}
