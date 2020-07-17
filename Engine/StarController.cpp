#include "StarController.h"
#include "Graphics.h"
#include "Starfield.h"

void StarController::Update( Star& model ) noexcept
{
	if( !Graphics::GetRect<float>().Contains( model.position ) )
	{
		model = Starfield::generate_star( rng, { 0.f, Graphics::GetRect<float>().Width() }, { 1.f, 2.f } );
	}
}
