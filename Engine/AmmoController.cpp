#include "AmmoController.h"
#include "Bullet.h"
#include "Graphics.h"
#include <algorithm>

namespace sns
{
	void EntityController<Ammo>::Update( Ammo& model, float dt ) noexcept
	{	
		model.isAlive = Graphics::IsVisible( RectI( AABB( model ) ) ) && model.energy > 0.f;
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
		return model.isAlive;
	}
}
