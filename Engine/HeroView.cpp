#include "HeroView.h"
#include "ShieldView.h"

void HeroView::Draw( Hero const& model, Graphics& gfx ) const noexcept
{
	gfx.DrawSprite( Hero::aabb + model.position, Radian{ 0.f }, sprite );

	auto shield_view = ShieldView{};
	shield_view.Draw( model.position, model.shield, gfx );
}
