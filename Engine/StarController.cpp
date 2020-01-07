#include "StarController.h"
#include "Graphics.h"
#include "Starfield.h"
#include "Star.h"
#include <random>

namespace sns
{
	void StarController::Update( Star& model ) noexcept
	{
		static std::mt19937 rng;
		if( !screenRect.Contains( model.position ) )
		{
			model = Starfield::generate_star( rng, { 0.f, screenRect.Width() }, { 1.f, 2.f } );
		}
	}
}
