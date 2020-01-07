#include "HeroView.h"
#include "Hero.h"
#include "ShieldView.h"

namespace sns
{
	void HeroView::Draw( Hero const& model, Graphics& gfx )noexcept
	{
		gfx.DrawSprite( Hero::aabb + model.position, Radian{ 0.f }, model.sprite );
		ShieldView::Draw( model.shield, model.position, gfx );
	}
}
