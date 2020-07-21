#include "AlphaTextureEffect.h"
#include "HeroView.h"
#include "Pipeline.h"
#include "PointSampler.h"
#include "ShieldView.h"
#include "SpriteEffect.h"

void HeroView::Draw( Hero const& model, SpriteCache const& cache, Graphics& gfx ) const noexcept
{
	auto pl = Pipeline{ AlphaTextureEffect<PointSampler>{}, gfx };
	auto rect = RectF::FromCenter(
		model.position,
		SizeF{ float( cache.hero_sprite.GetWidth() ), float( cache.hero_sprite.GetHeight() ) } *.5f
	);
	pl.vertices[ 0 ] = { { -.5f, -.5f }, { 0.f, 0.f } };
	pl.vertices[ 1 ] = { {  .5f, -.5f }, { 1.f, 0.f } };
	pl.vertices[ 2 ] = { { -.5f,  .5f }, { 0.f, 1.f } };
	pl.vertices[ 3 ] = { {  .5f,  .5f }, { 1.f, 1.f } };
	pl.PSSetTexture( cache.hero_sprite );
	pl.Draw( rect, Radian{} );
	/*gfx.DrawSprite(
		Hero::aabb + model.position, 
		cache.hero_sprite,
		SpriteEffect::Alpha{}
	);*/

	auto shield_view = ShieldView{};
	shield_view.Draw( model.position, model.shield, gfx );
}
