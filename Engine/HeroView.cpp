#include "EffectController.h"
#include "EffectView.h"
#include "HeroView.h"
#include "Hero.h"
#include "RectController.h"
#include "ShieldView.h"

namespace sns
{
	HeroView::Effect HeroView::effect;

	void HeroView::Draw( Hero const& model, Surface& render_target )noexcept
	{
		const auto width = RectController::Width( Hero::aabb );
		const auto height = RectController::Height( Hero::aabb );
		EffectController::VSSetConstantBuffer( effect, {
			Mat3F::Rotate( Radian{ Degree{90.f} } ) *
			Mat3F::Scale( width, height ) *
			Mat3F::Translation( model.position )
			} );
		EffectController::VSSetVertexBuffer( effect, vertices );
		EffectController::PSSetTexture( effect, model.sprite );
		EffectView::Draw( effect, render_target );

		ShieldView::Draw( model.shield, model.position, render_target );
	}
}
