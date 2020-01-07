#include "Boss1View.h"
#include "Bosses.h"

namespace sns
{
	void BossView::Draw( Boss const& model, Graphics & gfx )noexcept
	{
		std::visit( [ & ]( auto const& boss ) { Draw( boss, model, gfx ); }, model.variant );
	}

	void BossView::Draw( Boss1 const & boss, Boss const & parent, Graphics & gfx ) noexcept
	{
		gfx.DrawSprite( Boss1::aabb + parent.position, Radian{ parent.angle }, Boss1::sprite );
	}

	void BossView::Draw( Boss2 const & boss, Boss const & parent, Graphics & gfx ) noexcept
	{
		gfx.DrawSprite( Boss2::aabb + parent.position, Radian{ parent.angle }, Boss2::sprite );
	}
}
