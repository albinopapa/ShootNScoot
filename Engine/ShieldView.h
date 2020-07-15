#pragma once

#include "Graphics.h"
#include "Shield.h"

class ShieldView
{
public:
	void Draw( Vec2 const& position, Shield const& model, Graphics& gfx )const noexcept;

private:
	static const Surface sprite;
};
