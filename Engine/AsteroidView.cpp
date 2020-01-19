#include "Asteroids.h"
#include "AsteroidView.h"
#include "EffectController.h"
#include "EffectView.h"

namespace sns
{
	AsteroidView::Effect AsteroidView::effect;

	void AsteroidView::Draw( Asteroid const& model, Surface& render_target )noexcept
	{
		std::visit( [ & ]( auto const& asteroid )
		{
			using type = std::decay_t<decltype( asteroid )>;

			EffectController::VSSetConstantBuffer( effect, {
				Mat3F::Rotate( Radian{ 0.f } ) *
				Mat3F::Scale( type::radius * 2.f, type::radius * 2.f ) *
				Mat3F::Translation( model.position )
				} );

			EffectController::PSSetConstantBuffer(
				effect, { model.position, sqr( type::radius ) }
			);

			EffectController::VSSetVertexBuffer( effect, vertices );
		
			EffectView::Draw( effect, render_target );
		}, model.variant );

	}
}
