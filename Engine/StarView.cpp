#include "StarView.h"


	void StarView::Draw( Star const& model, Graphics& gfx ) const noexcept
	{
		gfx.DrawRect( model.rect + model.position, Degree{ 45.f }, Colors::White );
	}
