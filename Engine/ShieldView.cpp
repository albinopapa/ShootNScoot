#include "ShieldView.h"
#include <algorithm>

void ShieldView::Draw( Vec2 const& position, Shield const& model, Graphics& gfx ) const noexcept
{
	const auto t = uint32_t( 255.f * model.health * ( 1.f / Shield::recharge_max ) );
	const auto r = uint8_t( 255u - t );
	const auto g = uint8_t( t );
	const auto b = uint8_t( 0u );
	static constexpr auto rect = RectF{
		-Shield::radius,
		-Shield::radius,
		Shield::radius,
		Shield::radius
	};

	gfx.DrawCircle( Point( rect.Center() + position ), int( Shield::radius ), Color( r, g, b ) );
}
