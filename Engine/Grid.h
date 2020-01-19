#pragma once

#include "Cell.h"
#include "Settings.h"
#include <array>

namespace sns
{
	class Grid
	{
	private:
		friend class GridController;
		std::array<Cell, grid_size.width * grid_size.height> cells;
	};
}
