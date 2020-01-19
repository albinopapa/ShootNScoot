#include "EffectController.h"
#include "Mat3.h"
#include "RectController.h"
#include "Settings.h"
#include "Star.h"
#include "StarController.h"
#include "Starfield.h"
#include <random>

namespace sns
{
	void StarController::Update( Star& model ) noexcept
	{
		model.position += { 0.f, model.speed };

		static std::mt19937 rng;
		if( RectController::Contains( screen_rect, model.position ) ) return;

		constexpr auto range = std::pair{ -viewport_size.width * .5f, viewport_size.width * .5f };
		model = Starfield::generate_star( rng, range, { 1.f, 2.f } );
	}
}
