#include "AsteroidView.h"
#include "Pipeline.h"
#include "RasterStates.h"
#include "PointSampler.h"
#include "AlphaTextureEffect.h"

using AsteroidEffect = AlphaTextureEffect<PointSampler>;

void AsteroidView::Draw( Asteroid const& model, SpriteCache const& cache, Graphics& gfx ) const noexcept
{
	const auto& sprite = cache.asteroid_fames[ model.sprite_index ];
	const auto rect = RectF( sprite.GetRect() - sprite.GetRect().Center() ) + model.position;
	gfx.DrawSprite( rect, Radian{}, sprite, AsteroidEffect{} );
}
