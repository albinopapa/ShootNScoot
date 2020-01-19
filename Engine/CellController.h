#pragma once

#include "GridObject.h"
#include "Cell.h"

#include <vector>

namespace sns
{
	class Cell;
	struct CellController
	{
		static void AddObject( Cell& model, GridObject object_ );

		static void RemoveObject( Cell& model, GridObject object_ )noexcept;

		static auto FindObject( Cell const& model, GridObject object_ )noexcept->
			std::vector<GridObject>::const_iterator;

		static auto IsEmpty( Cell const& model )noexcept->bool;

		static auto Objects( Cell& model )noexcept->std::vector<GridObject>&;

		static void Clear( Cell& model )noexcept;

	};
}