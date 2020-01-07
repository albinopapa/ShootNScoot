#include "Hero.h"

namespace sns
{
	void Hero::Update( float dt )
	{
		position += ( velocity * ( Hero::max_speed * dt ) );

		weapon.Update( dt );
		shield.Update( dt );
	}

	Vec2 const & Hero::Position() const noexcept
	{
		return position;
	}

	float Hero::Health() const noexcept
	{
		return health;
	}
	
	void Hero::Reset() noexcept
	{
		weapon.Reset();
		shield.Reset();
		health = 100.f;
		velocity = { 0.f, 0.f };
		position = screenRect.Center();
	}
}