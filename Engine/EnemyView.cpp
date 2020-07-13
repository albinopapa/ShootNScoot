#include "EnemyView.h"
#include "Enemies.h"

namespace sns
{
	void EnemyView::Draw( Enemy const& model, Graphics& gfx ) const noexcept
	{
		std::visit( [ & ]( auto const& enemy )
		{
			using type = std::decay_t<decltype( enemy )>;
			gfx.DrawSprite( type::aabb + model.position, Radian{ 0.f }, sprite );
		}, model.variant );
	}
}
