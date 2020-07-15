#include "Boss1View.h"

void Boss1View::Draw( Boss1 const& model, Graphics & gfx ) const noexcept
{
	gfx.DrawSprite( Boss1::aabb + model.position, Radian{ 0.f }, sprite );
}
