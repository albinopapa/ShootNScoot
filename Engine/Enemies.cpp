#include "Enemies.h"

namespace sns
{
	Enemy::Enemy( EnemyType const& variant_ ) noexcept
		:
		variant( variant_ )
	{
		std::visit( [ & ]( auto& enemy )
		{
			using type = std::decay_t<decltype( enemy )>;
			waypoints = plot_curve( type::waypoints, 10 );
			position = waypoints[ 0 ];
		}, variant );
	}

	void Enemy::Update( float dt )
	{
		std::visit( [ & ]( auto& entity_ )
		{
			using type = std::decay_t<decltype( entity_ )>;
			position += ( velocity * ( type::speed * dt ) );
		}, variant );
	}

}
