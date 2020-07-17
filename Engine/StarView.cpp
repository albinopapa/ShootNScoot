#include "StarView.h"

void StarView::Draw( Star const& model, Graphics& gfx ) const noexcept
{
	gfx.DrawRect( model.rect + model.position, Colors::White );
}
