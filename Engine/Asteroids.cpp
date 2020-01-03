#include "Asteroids.h"
#include "ChiliMath.h"
#include <algorithm>

void sns::Asteroid::Update( float dt ) noexcept
{
	position += ( direction * ( dt * Asteroid::speed ) );
}

