#pragma once

#include "Asteroids.h"
#include "Enumerations.h"
#include "Rect.h"

class AsteroidController
{
public:
	void Update( Asteroid& model, float dt )noexcept;

	void TakeDamage( Asteroid& model, float amount )noexcept;
	void Reason( Asteroid& model, AsteroidDeathReason reason )noexcept;

	RectF AABB( Asteroid& model )const noexcept;
	float Damage( Asteroid& model )const noexcept;
	float Health( Asteroid& model )const noexcept;
	AsteroidDeathReason Reason( Asteroid& model )const noexcept;
	int ScoreValue( Asteroid& model )const noexcept;
};