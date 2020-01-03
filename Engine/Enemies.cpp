#include "Enemies.h"

void sns::Enemy::Update( float dt )
{
	auto do_update = [&](auto& entity_)
	{
		using type = std::decay_t<decltype( entity_ )>;
		position += ( velocity * ( type::speed * dt ) );
	};

	std::visit( do_update, variant );
}

