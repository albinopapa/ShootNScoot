#include "AnimationView.h"
#include "Animation.h"
#include "EffectController.h"
#include "EffectView.h"
#include "RectController.h"

AnimationView::Effect AnimationView::effect;
void AnimationView::Draw( Animation const& model, Vec2 const& pos, Surface& render_target, Color tint )noexcept
{
	EffectController::PSSetConstantBuffer( effect, { Colors::Magenta, tint } );
	EffectController::PSSetTexture( effect, model.sprite );

	const auto rect = RectF( model.frames[ model.iCurFrame ] ) + pos;
	const auto width = RectController::Width( rect );
	const auto height = RectController::Height( rect );

	EffectController::VSSetConstantBuffer( effect, {
		Mat3F::Scale( width, height ) *
		Mat3F::Translation( pos )
		} );
	EffectController::VSSetVertexBuffer( effect, vertices );

	EffectView::Draw( effect, render_target );
}
