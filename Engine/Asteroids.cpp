#include "Asteroids.h"
#include "ChiliMath.h"
#include <algorithm>

namespace sns
{
	Asteroid::Asteroid( Vec2 const & position_, Vec2 const & direction_, AsteroidType type ) noexcept
		:
		position( position_ ),
		direction( direction_ ),
		variant( type )
	{
	}

	void Asteroid::Update( float dt ) noexcept
	{
		position += ( direction * ( dt * Asteroid::speed ) );
	}

}
