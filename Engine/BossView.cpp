#include "Bosses.h"
#include "BossView.h"
#include "EffectController.h"
#include "EffectView.h"

namespace sns
{
	BossView::Effect BossView::effect;

	void BossView::Draw( Boss const& model, Surface& render_target )noexcept
	{
		std::visit( [ & ]( auto const& boss )
		{
			using type = std::decay_t<decltype( boss )>;

			EffectController::VSSetVertexBuffer( effect, vertices );
			EffectController::PSSetTexture( effect, type::sprite );

			const auto width = RectController::Width( type::aabb );
			const auto height = RectController::Height( type::aabb );

			EffectController::VSSetConstantBuffer( effect, {
				Mat3F::Rotate( Radian{ model.angle } ) *
				Mat3F::Scale( width, height ) *
				Mat3F::Translation( model.position )
				} );

			EffectView::Draw( effect, render_target );
		}, model.variant );
	}
}
