#pragma once

#include "Star.h"
#include "Vec2.h"
#include <random>

class StarController
{
public:
	void Update( Star& model )noexcept;

private:
	std::mt19937 rng;
};
