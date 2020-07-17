#include "StarController.h"
#include "Graphics.h"
#include "Starfield.h"
#include "Star.h"

	void StarController::Update( Star& model ) noexcept
	{
		if( !screenRect.Contains( model.position ) )
		{
			model = Starfield::generate_star( rng, { 0.f, screenRect.Width() }, { 1.f, 2.f } );
		}
	}
