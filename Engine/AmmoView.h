#pragma once

#include "Bullet.h"
#include "Graphics.h"
#include "ColorKeyTextureEffect.h"
#include "PointSampler.h"

using AmmoEffect = ColorKeyTextureEffect<PointSampler>;

class AmmoView
{
public:
	void Draw( Ammo const& model, Graphics& gfx )const noexcept;
	mutable AmmoEffect effect;
};
