#include "AlphaTextureEffect.h"
#include "HeroView.h"
#include "Pipeline.h"
#include "PointSampler.h"
#include "ShieldView.h"
#include "SpriteEffect.h"

void HeroView::Draw( Hero const& model, SpriteCache const& cache, Graphics& gfx ) const noexcept
{
	const auto size = 
		SizeF{ float( cache.hero_sprite.GetWidth() ), float( cache.hero_sprite.GetHeight() ) };
	
	gfx.DrawSprite(
		RectF::FromCenter( model.position, size * .5f ),
		Radian{},
		cache.hero_sprite,
		AlphaTextureEffect<PointSampler>{}
	);

	auto shield_view = ShieldView{};
	shield_view.Draw( model.position, model.shield, gfx );
}
