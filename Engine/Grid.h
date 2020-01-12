#pragma once

#include "Asteroids.h"
#include "Bosses.h"
#include "Bullet.h"
#include "Enemies.h"
#include "Hero.h"

#include "AmmoController.h"
#include "AsteroidController.h"
#include "BossController.h"
#include "EnemyController.h"
#include "EntityController.h"
#include "HeroController.h"
#include "ShieldController.h"
#include "model_type_traits.h"

#include <algorithm>
#include <array>
#include <optional>
#include <variant>
#include <vector>

namespace sns
{
	using GridObject = std::variant<Asteroid*, Ammo*, Boss*, Enemy*, Hero*>;

	template<typename T, typename U>
	void HandleCollision( T* ObjectA, U* ObjectB )noexcept
	{
		if constexpr( is_collidable_with<T, U> )
		{
			if constexpr( std::is_same_v<T, U> )
			{
				if( ObjectA == ObjectB ) return;
			}

			if( T::Controller::AABB( *ObjectA ).Overlaps( U::Controller::AABB( *ObjectB ) ) )
			{
				T::Controller::TakeDamage( *ObjectA, U::Controller::Damage( *ObjectB ) );
				U::Controller::TakeDamage( *ObjectB, T::Controller::Damage( *ObjectA ) );
			}
		}
	}

	class Cell
	{
	public:
		template<typename T> 
		void AddObject( T* object_ )
		{
			if( auto it = FindObject( object_ ); it == objects.end() )
				objects.push_back( object_ );
		}

		template<typename T>
		void RemoveObject( T* object_ )noexcept
		{
			if( auto it = FindObject( object_ ); it != objects.end() )
				objects.erase( it );
		}

		template<typename T>
		auto FindObject( T const* object )const noexcept->
			std::vector<GridObject>::const_iterator
		{
			auto is_same_address = [ & ]( auto const* pObject ) 
			{ 
				using type = std::decay_t<std::remove_pointer_t<decltype( pObject )>>;
				if constexpr( std::is_same_v<type, T> )
				{
					return object == pObject;
				}
				else
				{
					return false;
				}
			};

			for( auto it = objects.begin(), end = objects.end(); it != end; ++it )
			{
				if( std::visit( is_same_address, *it ) )
				{
					return it;
				}
			}

			return objects.end();
		}

		bool IsEmpty()const noexcept { return objects.empty(); }

		std::vector<GridObject>& Objects()noexcept
		{
			return objects;
		}
		
		void Clear()noexcept
		{
			objects = std::vector<GridObject>{};
		}
	public:
		static constexpr float size = 64.f;

	private:
		std::vector<GridObject> objects;
	};

	class Grid
	{
	public:
		using Controller = struct GridController;

	private:
		friend struct GridController;
		static constexpr int width  = ( ( Graphics::ScreenWidth + 63 ) & ~63 ) / 64;
		static constexpr int height = ( ( Graphics::ScreenHeight + 63 ) & ~63 ) / 64;
		static constexpr int hPadding = ( ( width * 64 ) - Graphics::ScreenWidth ) / 2;
		static constexpr int vPadding = ( ( height * 64 ) - Graphics::ScreenHeight ) / 2;
		std::array<Cell, width * height> cells;
	};

	struct GridController
	{
		template<typename Entity>
		static void AddObject( Grid& model, Entity& entity )noexcept
		{
			const auto& entity_rect = Entity::Controller::AABB( entity );

			const auto lt = FlattenIndex( Vec2{ entity_rect.left, entity_rect.top } );
			const auto rt = FlattenIndex( Vec2{ entity_rect.right, entity_rect.top } );
			const auto lb = FlattenIndex( Vec2{ entity_rect.left, entity_rect.bottom } );
			const auto rb = FlattenIndex( Vec2{ entity_rect.right, entity_rect.bottom } );

			model.cells[ lt ].AddObject( &entity );
			model.cells[ rt ].AddObject( &entity );
			model.cells[ lb ].AddObject( &entity );
			model.cells[ rb ].AddObject( &entity );
		}
		static void ClearCells(Grid& model)noexcept
		{
			for( auto& cell : model.cells )
			{
				cell.Clear();
			}
		}
		static std::array<Cell, Grid::width * Grid::height>const& Cells( Grid const& model )noexcept
		{
			return model.cells;
		}
		static std::array<Cell, Grid::width * Grid::height>& Cells( Grid& model )noexcept
		{
			return model.cells;
		}
	private:
		static int FlattenIndex( Vec2 const& position )noexcept
		{
			const auto x = ( int( position.x ) - Grid::hPadding ) / Cell::size;
			const auto y = ( int( position.y ) - Grid::vPadding ) / Cell::size;
			
			assert( x >= 0 );
			assert( x < Grid::width );
			assert( y >= 0 );
			assert( y < Grid::height );

			return x + ( y * Grid::width );
		}
	};
}
