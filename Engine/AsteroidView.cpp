#include "AsteroidView.h"
#include "Asteroids.h"

	void AsteroidView::Draw( Asteroid const& model, Graphics & gfx ) const noexcept
	{
		std::visit( [ & ]( auto const& asteroid )
		{
			using type = std::decay_t<decltype( asteroid )>;
			gfx.DrawCircle(model.position.x, model.position.y, type::radius, color);
			//gfx.DrawDisc( model.position, type::radius, color );
		}, model.variant );
	}

