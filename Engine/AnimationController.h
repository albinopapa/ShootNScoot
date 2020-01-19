#pragma once

#include "Animation.h"

class AnimationController
{
public:
	static void Update( Animation& model, float dt )noexcept;
private:
	static void Advance( Animation& model )noexcept;
};