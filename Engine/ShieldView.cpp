#include "EffectController.h"
#include "EffectView.h"
#include "RectController.h"
#include "ShieldView.h"
#include "Shield.h"
#include <algorithm>

namespace sns
{
	ShieldView::Effect ShieldView::effect;
	void ShieldView::Draw( Shield const& model, Vec2 const& position, Surface& render_target )noexcept
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
		constexpr auto width = RectController::Width( rect );
		constexpr auto height = RectController::Height( rect );
		EffectController::PSSetTexture( effect, Shield::sprite );
		EffectController::PSSetConstantBuffer( effect, { Colors::Magenta, Color( r, g, b ) } );
		EffectController::VSSetVertexBuffer( effect, vertices );
		EffectController::VSSetConstantBuffer( effect, {
			Mat3F::Scale( width, height ) *
			Mat3F::Translation( position )
			} );

		EffectView::Draw( effect, render_target );
	}
}
