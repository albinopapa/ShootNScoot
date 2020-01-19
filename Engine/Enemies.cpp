#include "Enemies.h"

namespace sns
{
	Enemy::Enemy( std::vector<Vec2> waypoints_, EnemyType const& variant_ ) noexcept
		:
		variant( variant_ )
	{
		waypoints = plot_curve( std::move( waypoints_ ), 10 );
		position = waypoints[ 0 ];
	}
}
