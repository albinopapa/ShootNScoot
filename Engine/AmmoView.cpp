#include "AmmoView.h"
#include <cassert>


void AmmoView::Draw( Ammo const& model, Graphics& gfx ) const noexcept
{
	std::visit( [&]( auto const& ammo )
	{
		using type = std::decay_t<decltype( ammo )>;
		effect.ps.buffer = { Colors::Magenta, Colors::White };
		gfx.DrawSprite( 
			type::aabb + model.position, 
			Radian{},
			type::sprite, 
			effect
		);
	}, model.variant );
}
