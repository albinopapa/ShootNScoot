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
	
	auto pl = Pipeline{ AsteroidEffect{}, gfx };
	pl.PSSetTexture( sprite );
	pl.vertices[ 0 ] = { { -.5f, -.5f }, { 0.f, 0.f } };
	pl.vertices[ 1 ] = { {  .5f, -.5f }, { 1.f, 0.f } };
	pl.vertices[ 2 ] = { { -.5f,  .5f }, { 0.f, 1.f } };
	pl.vertices[ 3 ] = { {  .5f,  .5f }, { 1.f, 1.f } };

	pl.Draw( rect, Radian{} );
}
