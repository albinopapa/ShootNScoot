#include "Ammo.h"
#include "AmmoView.h"
#include "EffectController.h"
#include "EffectView.h"
#include "RectController.h"
#include <type_traits>

namespace sns
{
	ColorKeyTextureEffect<PointSampler> AmmoView::effect;
	void AmmoView::Draw( Ammo const& model, Surface& render_target )noexcept
	{
		std::visit( [ & ]( auto const& ammo )
		{
			using type = std::decay_t<decltype( ammo )>;

			const auto width = RectController::Width( type::aabb );
			const auto height = RectController::Height( type::aabb );

			EffectController::PSSetTexture( effect, type::sprite );
			EffectController::VSSetConstantBuffer( effect, {
				Mat3F::Rotate( Radian{ 0.f } ) *
				Mat3F::Scale( width, height ) *
				Mat3F::Translation( model.position )
				} );
			EffectController::VSSetVertexBuffer( effect, vertices );
			EffectView::Draw( effect, render_target );
		}, model.variant );
	}
}
