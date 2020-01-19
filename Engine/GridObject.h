#pragma once

#include "Ammo.h"
#include "Asteroids.h"
#include "Bosses.h"
#include "Enemies.h"
#include "Hero.h"

#include <variant>

namespace sns
{
	using GridObject = std::variant<Asteroid*, Ammo*, Boss*, Enemy*, Hero*>;
}