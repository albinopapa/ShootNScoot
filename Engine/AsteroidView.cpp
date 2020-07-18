#include "AsteroidView.h"

void AsteroidView::Draw( Asteroid const& model, Graphics& gfx ) const noexcept
{
	std::visit( [&]( auto const& asteroid )
	{
		using type = std::decay_t<decltype( asteroid )>;
		gfx.DrawDisc( Point( model.position ), int( type::radius ), color );
	}, model.variant );
}
