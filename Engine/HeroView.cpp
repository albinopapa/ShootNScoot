#include "HeroView.h"
#include "ShieldView.h"
#include "SpriteEffect.h"

void HeroView::Draw( Hero const& model, SpriteCache const& cache, Graphics& gfx ) const noexcept
{
	gfx.DrawSprite( 
		Hero::aabb + model.position, 
		cache.hero_sprite,
		SpriteEffect::Alpha{}
	);

	auto shield_view = ShieldView{};
	shield_view.Draw( model.position, model.shield, gfx );
}
