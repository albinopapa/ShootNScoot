#include "AmmoController.h"
#include "AsteroidController.h"
#include "BossController.h"
#include "CellController.h"
#include "EnemyController.h"
#include "Grid.h"
#include "GridController.h"
#include "HeroController.h"
#include <cassert>

namespace sns
{
	void GridController::AddObject( Grid & model, GridObject entity ) noexcept
	{
		std::visit( [ & ]( auto* pEntity )
		{
			using Entity = std::remove_pointer_t<decltype( pEntity )>;
			const auto& entity_rect = EntityController<Entity>::AABB( *pEntity );

			const auto lt = FlattenIndex( Vec2{ entity_rect.left, entity_rect.top } );
			const auto rt = FlattenIndex( Vec2{ entity_rect.right, entity_rect.top } );
			const auto lb = FlattenIndex( Vec2{ entity_rect.left, entity_rect.bottom } );
			const auto rb = FlattenIndex( Vec2{ entity_rect.right, entity_rect.bottom } );

			CellController::AddObject( model.cells[ lt ], pEntity );
			CellController::AddObject( model.cells[ rt ], pEntity );
			CellController::AddObject( model.cells[ lb ], pEntity );
			CellController::AddObject( model.cells[ rb ], pEntity );
		}, entity );
	}

	void GridController::ClearCells( Grid & model ) noexcept
	{
		for( auto& cell : model.cells )
		{
			CellController::Clear( cell );
		}
	}

	auto GridController::Cells( Grid const & model ) noexcept->decltype( Grid::cells )const &
	{
		return model.cells;
	}

	auto GridController::Cells( Grid& model ) noexcept->decltype( Grid::cells )&
	{
		return model.cells;
	}

	int GridController::FlattenIndex( Vec2 const & position ) noexcept
	{
		const auto x = int( position.x + world_rect.right ) / cell_size;
		const auto y = int( position.y + world_rect.bottom ) / cell_size;

		assert( x >= 0 );
		assert( x < grid_size.width );
		assert( y >= 0 );
		assert( y < grid_size.height );

		return x + ( y * grid_size.width );
	}

}