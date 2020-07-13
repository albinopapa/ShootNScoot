#include "Asteroids.h"
#include "ChiliMath.h"
#include <algorithm>

void Asteroid::Update( float dt ) noexcept
{
	position += ( direction * ( dt * Asteroid::speed ) );
}

