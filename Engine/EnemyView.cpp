#include "EffectController.h"
#include "EffectView.h"
#include "Enemies.h"
#include "EnemyView.h"
#include "RectController.h"

namespace sns
{
	EnemyView::Effect EnemyView::effect;

	void EnemyView::Draw( Enemy const& model, Surface& render_target )noexcept
	{
		std::visit( [ & ]( auto const& enemy )
		{
			using type = std::decay_t<decltype( enemy )>;

			const auto width = RectController::Width( type::aabb );
			const auto height = RectController::Height( type::aabb );

			EffectController::PSSetTexture( effect, type::sprite );
			EffectController::VSSetVertexBuffer( effect, vertices );
			EffectController::VSSetConstantBuffer( effect, {
					Mat3F::Rotate( Radian{ model.angle } ) *
					Mat3F::Scale( width, height ) *
					Mat3F::Translation( model.position )
				} );

			EffectView::Draw( effect, render_target );

		}, model.variant );
	}
}
