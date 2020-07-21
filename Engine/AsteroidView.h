#pragma once

#include "Asteroids.h"
#include "Graphics.h"
#include "SpriteCache.h"

class AsteroidView
{
public:
	void Draw( Asteroid const& model, SpriteCache const& cache, Graphics& gfx )const noexcept;
private:
	static constexpr Color color = Color{ 200, 100, 50 };
};
