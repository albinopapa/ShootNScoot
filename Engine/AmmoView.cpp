#include "AmmoView.h"
#include <cassert>

void AmmoView::Draw( Ammo const& model, Graphics& gfx ) const noexcept
{
	std::visit( [&]( auto const& ammo )
	{
		using type = std::decay_t<decltype( ammo )>;

		gfx.DrawSprite( type::aabb + model.position, Radian( 0.f ), type::sprite );
	}, model.variant );
}
