#include "AmmoView.h"
#include "SpriteEffect.h"
#include <cassert>

void AmmoView::Draw( Ammo const& model, Graphics& gfx ) const noexcept
{
	std::visit( [&]( auto const& ammo )
	{
		using type = std::decay_t<decltype( ammo )>;

		gfx.DrawSprite( 
			type::aabb + model.position, 
			type::sprite, 
			SpriteEffect::Chroma{ Colors::Magenta } 
		);
	}, model.variant );
}
