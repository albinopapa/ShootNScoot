#include "HeroView.h"
#include "Hero.h"
#include "ShieldView.h"

namespace sns
{
	void HeroView::Draw( Hero const& model, Graphics& gfx ) const noexcept
	{
		const RectI rect = { int(model.position.x) - herohalfwidth,int(model.position.y) - herohalfheight,
			int(model.position.x) + herohalfwidth,int(model.position.y) + herohalfheight };
		//gfx.DrawSprite( Hero::aabb + model.position, Radian{ 0.f }, sprite );
		gfx.DrawRect(rect, Colors::Magenta);
		auto shield_view = ShieldView{};
		shield_view.Draw( model.position, model.shield, gfx );
	}
}
