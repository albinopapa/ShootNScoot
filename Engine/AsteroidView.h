#pragma once
#include "Asteroids.h"
#include "Graphics.h"

	class AsteroidView
	{
	public:
		void Draw( Asteroid const& model, Graphics& gfx )const noexcept;
	private:
		static constexpr Color color = Color{ 200, 100, 50 };
	};
