#include "Ammo.h"
#include "AmmoController.h"
#include "RectController.h"
#include "Settings.h"
#include <algorithm>
#include <type_traits>

namespace sns
{
	void EntityController<Ammo>::Update( Ammo& model, float dt ) noexcept
	{	
		std::visit( [ & ]( const auto& ammo_ ) 
		{
			using type = std::decay_t<decltype( ammo_ )>;

			model.position += ( model.velocity * ( type::speed * dt ) );
		}, model.variant );
	}

	void  EntityController<Ammo>::TakeDamage( Ammo& model, float amount ) noexcept
	{
		model.energy -= amount;
		model.energy = std::max( model.energy, 0.f );
	}
	Ammo::Owner EntityController<Ammo>::GetOwner( Ammo const & model ) noexcept
	{
		return model.owner;
	}
	float EntityController<Ammo>::Damage( Ammo const& model )noexcept
	{
		return std::visit( [ & ]( const auto& ammo_ ) {
			using type = std::decay_t<decltype( ammo_ )>;
			return type::damage * ( model.energy / type::max_energy );
		}, model.variant );
	}
	RectF EntityController<Ammo>::AABB( Ammo const& model )noexcept
	{
		return std::visit( [ & ]( const auto& ammo ) {
			return std::decay_t<decltype( ammo )>::aabb + model.position;
		}, model.variant );
	}

	bool EntityController<Ammo>::IsAlive( Ammo const& model )noexcept
	{
		return 
			RectController::IsContainedBy( AABB( model ), world_rect ) &&
			model.energy > 0.f;
	}
}
