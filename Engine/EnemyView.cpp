#include "EnemyView.h"
#include "Enemies.h"
#include "AlphaTextureEffect.h"
#include "Pipeline.h"
#include "PointSampler.h"
#include "SpriteEffect.h"

void EnemyView::Draw( Enemy const& model, SpriteCache const& cache, Graphics& gfx ) const noexcept
{
	std::visit( [&]( auto const& enemy ) {
		const auto& sprite = PickSprite( enemy, cache );
		DrawSprite( model.position, model.m_angle, sprite, gfx );
	}, model.variant );
}

Surface const& EnemyView::PickSprite( Enemy1 const& enemy, SpriteCache const& cache )const noexcept 
{ 
	return cache.enemy1_ship; 
}
Surface const& EnemyView::PickSprite( Enemy2 const& enemy, SpriteCache const& cache )const noexcept 
{ 
	return cache.enemy2_ship; 
}
Surface const& EnemyView::PickSprite( Enemy3 const& enemy, SpriteCache const& cache )const noexcept 
{ 
	return cache.enemy3_ship; 
}
Surface const& EnemyView::PickSprite( Enemy4 const& enemy, SpriteCache const& cache )const noexcept 
{ 
	return cache.enemy4_ship; 
}
Surface const& EnemyView::PickSprite( Enemy5 const& enemy, SpriteCache const& cache )const noexcept 
{ 
	return cache.enemy1_ship; 
}

void EnemyView::DrawSprite( Vec2 const& position, Radian angle, Surface const& sprite, Graphics& gfx )const noexcept
{
	const auto size = SizeF{ float( sprite.GetWidth() ), float( sprite.GetHeight() ) } *.5f;
	gfx.DrawSprite( 
		RectF::FromCenter( position, size ), 
		-angle, 
		sprite, 
		AlphaTextureEffect<PointSampler>{} 
	);
}
