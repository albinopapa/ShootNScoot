#include "ShieldView.h"
#include "Shield.h"
#include <algorithm>

namespace sns
{
	void ShieldView::Draw( Shield const& model, Vec2 const& position, Graphics & gfx )noexcept
	{
		const auto t = uint32_t( 255.f * model.health / Shield::recharge_max );
		const auto r = uint8_t( 255u - t );
		const auto g = uint8_t( t );
		const auto b = uint8_t( 0u );
		constexpr auto rect = RectF{
			-Shield::radius,
			-Shield::radius,
			Shield::radius,
			Shield::radius
		};
		gfx.DrawSprite( rect + position, Radian{ 0.f }, Shield::sprite, Color( r, g, b ) );
	}
}
