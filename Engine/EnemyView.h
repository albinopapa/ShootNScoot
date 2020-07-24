#pragma once

#include "Enemies.h"
#include "Graphics.h"
#include "SpriteCache.h"

class EnemyView
{
public:
	void Draw( Enemy const& model, SpriteCache const& cache, Graphics& gfx )const noexcept;

private:
	Surface const& PickSprite( Enemy1 const& enemy, SpriteCache const& cache )const noexcept;
	Surface const& PickSprite( Enemy2 const& enemy, SpriteCache const& cache )const noexcept;
	Surface const& PickSprite( Enemy3 const& enemy, SpriteCache const& cache )const noexcept;
	Surface const& PickSprite( Enemy4 const& enemy, SpriteCache const& cache )const noexcept;
	Surface const& PickSprite( Enemy5 const& enemy, SpriteCache const& cache )const noexcept;

	void DrawSprite( Vec2 const& position, Radian angle, Surface const& sprite, Graphics& gfx )const noexcept;
};
