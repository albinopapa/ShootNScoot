#include "Bosses.h"
#include "World.h"
#include <cassert>

namespace sns
{
	Boss::Boss( BossType type ) noexcept
		:
		variant( type )
	{}
}
