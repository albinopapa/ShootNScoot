#pragma once

#include "Bullet.h"
#include "Graphics.h"

class AmmoView
{
public:
	void Draw( Ammo const& model, Graphics& gfx )const noexcept;
};
