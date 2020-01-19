#include "WeaponController.h"
#include "Ammo.h"
#include "World.h"
#include "WorldController.h"

namespace sns
{
	void WeaponController::Update( Weapon& model, float dt )noexcept
	{
		if( model.state == Weapon::State::Recharge )
		{
			model.fire_timer -= dt;
			if( model.fire_timer <= 0.f )
			{
				model.state = Weapon::State::Idle;
			}
		}
	}
	bool WeaponController::CanFire( Weapon const& model )noexcept
	{
		return model.state == Weapon::State::Idle;
	}
	void WeaponController::Fire( 
		Weapon& model,
		Vec2 const & position, 
		Vec2 const & direction, 
		World& world, 
		Ammo::Owner ammo_owner )
	{
		if( model.state == Weapon::State::Idle )
		{
			std::visit( [ & ]( auto& weapon ) {
				using type = std::decay_t<decltype( weapon )>;
				
				WorldController::SpawnAmmo(
					world, Ammo{ position, direction, ammo_owner, type::ammo_type{} } 
				);

				model.state = Weapon::State::Recharge;

				model.fire_timer = type::fire_delay;
			}, model.variant );
		}
	}
	void WeaponController::Reset( Weapon & model ) noexcept
	{
		model.variant = Gun{};
		model.fire_timer = 0.f;
		model.state = Weapon::State::Idle;
	}
}
