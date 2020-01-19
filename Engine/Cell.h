#pragma once

#include "GridObject.h"
#include <vector>

namespace sns
{
	class Cell
	{
	private:
		friend struct CellController;
		std::vector<GridObject> objects;
	};
}