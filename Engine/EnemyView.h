#pragma once

#include "Enemies.h"
#include "Graphics.h"
#include "SpriteCache.h"

class EnemyView
{
public:
	void Draw( Enemy const& model, SpriteCache const& cache, Graphics& gfx )const noexcept;

private:
	void Draw( Enemy const& parent, Enemy1 const& enemy, SpriteCache const& cache, Graphics& gfx )const noexcept;
	void Draw( Enemy const& parent, Enemy2 const& enemy, SpriteCache const& cache, Graphics& gfx )const noexcept;
	void Draw( Enemy const& parent, Enemy3 const& enemy, SpriteCache const& cache, Graphics& gfx )const noexcept;
	void Draw( Enemy const& parent, Enemy4 const& enemy, SpriteCache const& cache, Graphics& gfx )const noexcept;
	void Draw( Enemy const& parent, Enemy5 const& enemy, SpriteCache const& cache, Graphics& gfx )const noexcept;

	std::size_t GetFrame( Degree angle )const noexcept;
};
