#include "AsteroidSpawner.h"
#include "Asteroids.h"
#include "World.h"

void AsteroidSpawner::Update( World& world, float dt )
{
	switch( state )
	{
		case State::Idle:
			spawn_timer -= dt;
			if( spawn_timer <= 0.f )
			{
				if( spawn_count < AsteroidSpawner::spawn_max )
					state = State::Spawning;
				else
					state = State::Complete;
			}
			break;
		case State::Spawning:
		{
			constexpr auto cx = screenRect.Center().x;
			constexpr auto cy = screenRect.Center().y;
			const auto pos = Vec2{ xDist( rng ), -50.f };
			const auto dir = Vec2{ pos.x > cx ? -vxDist( rng ) : vxDist( rng ), 1.f }.Normalize();
			spawn_timer = AsteroidSpawner::spawn_delay;
			
			world.SpawnAsteroid( Asteroid{ BigAsteroid{}, pos, dir } );

			++spawn_count;
			state = State::Idle;
			break;
		}
		default:
			break;
	}
}

void AsteroidSpawner::Reset() noexcept
{
	spawn_timer				= AsteroidSpawner::spawn_delay;
	spawn_count				= 0;
	state					= State::Idle;
}
