#include "EnemyView.h"
#include "Enemies.h"

namespace sns
{
	void EnemyView::Draw( Enemy const& model, Graphics& gfx )noexcept
	{
		std::visit( [ & ]( auto const& enemy )
		{
			using type = std::decay_t<decltype( enemy )>;
			const auto angle_offset = Radian{ Degree{ 90.f } };
			const auto angle = Radian{ model.angle };
			gfx.DrawSprite( type::aabb + model.position, angle_offset + angle, type::sprite );
		}, model.variant );
	}
}
