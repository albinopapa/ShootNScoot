#include "AsteroidView.h"
#include "Asteroids.h"

namespace sns
{
	void AsteroidView::Draw( Asteroid const& model, Graphics & gfx ) const noexcept
	{
		std::visit( [ & ]( auto const& asteroid )
		{
			using type = std::decay_t<decltype( asteroid )>;
			gfx.DrawDisc( model.position, type::radius, color );
		}, model.variant );
	}
}
