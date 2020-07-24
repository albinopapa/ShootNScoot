#include "Boss1View.h"
#include "AlphaTextureEffect.h"
#include "PointSampler.h"

// Just a note for later if we decide to do some postprocessing effects
// (0.2126*R + 0.7152*G + 0.0722*B) calculate luminance 

// constexpr auto rconst = std::uint32_t( .2126f * 255.f );
// constexpr auto gconst = std::uint32_t( .7152f * 255.f );
// constexpr auto bconst = std::uint32_t( .0722f * 255.f );

// My thinking is we find the luminance of a pixel and if above a certain value, 
// create a separate surface of all the pixels above that value.  Then we can 
// incorporate a bloom effect ( I think chili did something similar in his HUGS tutorials )

void Boss1View::Draw( Boss1 const& model, Graphics & gfx ) const noexcept
{
	gfx.DrawSprite( Boss1::aabb + model.position, Radian{}, sprite, AlphaTextureEffect<PointSampler>{} );
}
