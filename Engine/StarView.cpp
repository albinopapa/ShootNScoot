#include "StarView.h"
#include "Star.h"

namespace sns
{
	void StarView::Draw( Star const& model, Graphics& gfx )noexcept
	{
		gfx.DrawRect( model.rect + model.position, Degree{ 45.f }, Colors::White );
	}
}