#include "EffectController.h"
#include "EffectView.h"
#include "Star.h"
#include "StarView.h"

namespace sns
{
	RectFillEffect StarView::effect;
	void StarView::Draw( Star const& model, Surface& render_target )noexcept
	{
		constexpr auto angle = Radian{ Degree{ 45.f } };
		constexpr auto width = RectController::Width( Star::rect );
		constexpr auto height = RectController::Height( Star::rect );

		EffectController::VSSetVertexBuffer( effect, vertices );
		EffectController::VSSetConstantBuffer( effect, {
			Mat3F::Rotate( angle ) *
			Mat3F::Scale( width, height ) *
			Mat3F::Translation( model.position )
			} );
		EffectView::Draw( effect, render_target );
	}
}