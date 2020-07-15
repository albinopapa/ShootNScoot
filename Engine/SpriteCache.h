#pragma once

// NOTE: This file may not be needed
// TODO: Determine if a central location for sprites is necessary

#include "Surface.h"
#include <vector>

struct SpriteCache
{
	Surface hero_sprite;
	Surface enemy_sprite;
	Surface bullet_sprite;
	Surface asteroid_sprite;
	Surface plasmaball_sprite;
	std::vector<Surface> ship1_frames;
};
