#include "BossView.h"
#include "Bosses.h"

namespace sns
{
	void BossView::Draw( Boss const& model, Graphics & gfx )noexcept
	{
		std::visit( [ & ]( auto const& boss ) { Draw( boss, model, gfx ); }, model.variant );
	}

	void BossView::Draw( Boss1 const& boss, Boss const & parent, Graphics & gfx ) noexcept
	{
		gfx.DrawSprite( Boss1::aabb + parent.position, Radian{ parent.angle }, Boss1::sprite );
	}

	void BossView::Draw( Boss2 const& boss, Boss const & parent, Graphics & gfx ) noexcept
	{
		gfx.DrawSprite( Boss2::aabb + parent.position, Radian{ parent.angle }, Boss2::sprite );
	}

	void BossView::Draw( Boss3 const& boss, Boss const& parent, Graphics& gfx )noexcept 
	{
		gfx.DrawSprite( Boss3::aabb + parent.position, Radian{ parent.angle }, Boss3::sprite );
	}

	void BossView::Draw( Boss4 const& boss, Boss const& parent, Graphics& gfx )noexcept
	{
		gfx.DrawSprite( Boss4::aabb + parent.position, Radian{ parent.angle }, Boss4::sprite );
	}

	void BossView::Draw( Boss5 const& boss, Boss const& parent, Graphics& gfx )noexcept
	{
		gfx.DrawSprite( Boss5::aabb + parent.position, Radian{ parent.angle }, Boss5::sprite );
	}

	void BossView::Draw( Boss6 const& boss, Boss const& parent, Graphics& gfx )noexcept
	{
		gfx.DrawSprite( Boss6::aabb + parent.position, Radian{ parent.angle }, Boss6::sprite );
	}

	void BossView::Draw( Boss7 const& boss, Boss const& parent, Graphics& gfx )noexcept
	{
		gfx.DrawSprite( Boss7::aabb + parent.position, Radian{ parent.angle }, Boss7::sprite );
	}

	void BossView::Draw( Boss8 const& boss, Boss const& parent, Graphics& gfx )noexcept
	{
		gfx.DrawSprite( Boss8::aabb + parent.position, Radian{ parent.angle }, Boss8::sprite );
	}

	void BossView::Draw( Boss9 const& boss, Boss const& parent, Graphics& gfx )noexcept
	{
		gfx.DrawSprite( Boss9::aabb + parent.position, Radian{ parent.angle }, Boss9::sprite );
	}

	void BossView::Draw( Boss10 const& boss, Boss const& parent, Graphics& gfx )noexcept
	{
		gfx.DrawSprite( Boss10::aabb + parent.position, Radian{ parent.angle }, Boss10::sprite );
	}
}
