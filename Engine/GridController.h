#pragma once

#include "Grid.h"
#include "GridObject.h"
#include "Settings.h"

namespace sns
{
	class GridController
	{
	public:
		static void AddObject( Grid& model, GridObject entity )noexcept;

		static void ClearCells( Grid& model )noexcept;

		static auto Cells( Grid const& model )noexcept->decltype(Grid::cells)const&;

		static auto Cells( Grid& model )noexcept->decltype( Grid::cells )&;

	private:
		static int FlattenIndex( Vec2 const& position )noexcept;
	};

}