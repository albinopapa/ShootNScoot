#include "AmmoController.h"
#include "Bullet.h"
#include "Graphics.h"
#include <algorithm>

namespace sns
{
	void AmmoController::Update( Ammo& model, float dt ) noexcept
	{	
		model.isAlive = Graphics::IsVisible( RectI( AABB( model ) ) ) && model.energy > 0.f;
	}

	void  AmmoController::TakeDamage( Ammo& model, float amount ) noexcept
	{
		model.energy -= amount;
		model.energy = std::max( model.energy, 0.f );
	}
	float AmmoController::Damage( Ammo const& model ) const noexcept
	{
		return std::visit( [ & ]( const auto& ammo_ ) {
			using type = std::decay_t<decltype( ammo_ )>;
			return type::damage * ( model.energy / type::max_energy );
		}, model.variant );
	}
	RectF AmmoController::AABB( Ammo const& model ) const noexcept
	{
		return std::visit( [ & ]( const auto& ammo ) {
			return std::decay_t<decltype( ammo )>::aabb + model.position;
		}, model.variant );
	}

	bool AmmoController::IsAlive( Ammo const& model ) const noexcept
	{
		return model.isAlive;
	}
}
