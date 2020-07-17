#include "EnemyView.h"
#include "Enemies.h"
#include "SpriteEffect.h"

void EnemyView::Draw( Enemy const& model, SpriteCache const& cache, Graphics& gfx ) const noexcept
{
	std::visit( [&]( auto const& enemy ) { Draw( model, enemy, cache, gfx ); }, model.variant );
}

void EnemyView::Draw( Enemy const& parent, Enemy1 const& enemy, SpriteCache const& cache, Graphics& gfx )const noexcept {
	const auto& sprite = cache.ship1_frames[ GetFrame( enemy.m_angle ) ];
	
	const auto offset = 
		Point( parent.position ) - 
		Point{ sprite.GetWidth() / 2, sprite.GetHeight() / 2 };

	gfx.DrawSprite( 
		sprite.GetRect() + offset,
		sprite, 
		SpriteEffect::Alpha{}
	);
}
void EnemyView::Draw( Enemy const& parent, Enemy2 const& enemy, SpriteCache const& cache, Graphics& gfx )const noexcept {
	const auto& sprite = cache.ship2_frames[ GetFrame( enemy.m_angle ) ];

	const auto offset =
		Point( parent.position ) -
		Point{ sprite.GetWidth() / 2, sprite.GetHeight() / 2 };

	gfx.DrawSprite(
		sprite.GetRect() + offset,
		sprite,
		SpriteEffect::Alpha{}
	);
}
void EnemyView::Draw( Enemy const& parent, Enemy3 const& enemy, SpriteCache const& cache, Graphics& gfx )const noexcept {

}
void EnemyView::Draw( Enemy const& parent, Enemy4 const& enemy, SpriteCache const& cache, Graphics& gfx )const noexcept {

}
void EnemyView::Draw( Enemy const& parent, Enemy5 const& enemy, SpriteCache const& cache, Graphics& gfx )const noexcept {

}

std::size_t EnemyView::GetFrame( Degree angle ) const noexcept
{
	if( angle >= -112.5f && angle < -67.5f ) {
		return 0;
	}
	else if( angle >= -67.5f && angle < -22.5f ) {
		return 1;
	}
	else if( angle >= -22.5f && angle < 22.5f ) {
		return 2;
	}
	else if( angle >= 22.5f && angle < 67.5f ) {
		return 3;
	}
	else if( angle >= 67.5f && angle < 112.f ) {
		return 4;
	}
	else if( angle >= -157.5f && angle < -112.f ) {
		return 5;
	}
	else if( std::abs( angle ) >= 157.5f && std::abs( angle ) < 180.f ) {
		return 6;
	}
	else if( angle >= 112.f && angle < 157.5f ) {
		return 7;
	}
	
}
