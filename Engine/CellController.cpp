#include "CellController.h"
#include "Cell.h"
#include <algorithm>

namespace sns
{
	void CellController::AddObject( Cell & model, GridObject object_ )
	{
		if( auto it = FindObject( model, object_ ); it == model.objects.end() )
			model.objects.push_back( object_ );
	}
	void CellController::RemoveObject( Cell & model, GridObject object_ ) noexcept
	{
		if( auto it = FindObject( model, object_ ); it != model.objects.end() )
			model.objects.erase( it );
	}
	auto CellController::FindObject( Cell const & model, GridObject object_ ) noexcept -> std::vector<GridObject>::const_iterator
	{
		auto is_same_address = [ & ]( auto const* pObjectA, auto const* pObjectB )
		{
			using T = std::decay_t<decltype( *pObjectA )>;
			using U = std::decay_t<decltype( *pObjectB )>;
			if constexpr( std::is_same_v<T, U> )
			{
				return pObjectA == pObjectB;
			}
			else
			{
				return false;
			}
		};

		auto find_visitor = [ & ]( GridObject const& gObject )
		{
			return std::visit( is_same_address, gObject, object_ );
		};
		
		return std::find_if( model.objects.begin(), model.objects.end(), find_visitor );
	}
	auto CellController::IsEmpty( Cell const & model )noexcept->bool
	{
		return model.objects.empty();
	}
	auto CellController::Objects( Cell & model )noexcept -> std::vector<GridObject>&
	{
		return model.objects;
	}
	void CellController::Clear( Cell & model ) noexcept
	{
		model.objects = std::vector<GridObject>{};
	}
}
