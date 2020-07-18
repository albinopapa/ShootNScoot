#include "Hero.h"
#include "World.h"

void Hero::Update( float dt )
{
	position += ( velocity * ( Hero::max_speed * dt ) );

	weapon.Update( dt );
	shield.Update( dt );
}

void Hero::Reset() noexcept
{
	weapon.Reset();
	shield.Reset();
	health = 100.f;
	velocity = { 0.f, 0.f };
	position = Graphics::GetRect<float>().Center();
}
