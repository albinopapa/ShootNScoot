#pragma once

template<typename Container, typename Pred>
void erase_if( Container& container_, Pred pred_ )noexcept
{
	auto last_elem = 
		std::remove_if( container_.begin(), container_.end(), pred_ );

	container_.erase( last_elem, container_.end() );
}

#include "Vec2.h"
#include <cassert>
#include <vector>

template<typename T>
class AnchorPoints
{
public:
	AnchorPoints() = default;
	AnchorPoints( std::vector<T> _points )
		:
		points( std::move( _points ) )
	{
	}
	template<typename Iter>
	AnchorPoints( Iter first, Iter end )
		:
		points( end - first )
	{
		for( auto& point : points )
		{
			point = *first;
			++first;
		}
	}

	void AddPoint( const T& _point )noexcept
	{
		points.push_back( _point );
	}

	template<typename...Data> void AddPoint( Data&&... data )
	{
		points.emplace_back( std::forward<Data>( data )... );
	}

	T& operator[]( int i )
	{
		return points[ i ];
	}

	const T& operator[]( int i )const
	{
		return points[ i ];
	}

	int Count()const noexcept
	{
		return int( points.size() );
	}

	std::vector<T>& GetPoints()noexcept
	{
		return points;
	}

	const std::vector<T>& GetPoints()const noexcept
	{
		return points;
	}

private:
	std::vector<T> points;
};

template<typename T>
class Bezier
{
public:
	Bezier() = default;

	Bezier( std::uint32_t numSections, AnchorPoints<T> _anchors )
		:
		sections( numSections ),
		anchors( std::move( _anchors ) )
	{
		points.reserve( sections );

		for( std::uint32_t i = 0u; i <= sections; ++i )
		{
			const auto t = static_cast< float >( i ) / static_cast< float >( sections );
			points.push_back( PlotControlPoint( t ) );
		}
	}

	auto const& operator[]( int index )const noexcept
	{
		assert( index < int( points.size() ) );
		return points[ index ];
	}

	auto Count()const noexcept
	{
		return int( points.size() );
	}

	auto const& GetControlPoints()const noexcept
	{
		return points;
	}

private:
	auto PlotControlPoint( float _t )const noexcept
	{
		switch( anchors.Count() )
		{
			case 0: return T{};
			case 1: return anchors[ 0 ];
			case 3: return PlotQuadratic( _t );
			case 4: return PlotCubic( _t );
			default: return PlotUknown( _t );	// Also handles linear interpolation of two points
		}
	}
	auto PlotQuadratic( float _t )const noexcept
	{
		const auto range0 = ( anchors[ 1 ] - anchors[ 0 ] );
		const auto range1 = ( anchors[ 2 ] - anchors[ 1 ] );
		const auto range2 = ( range1 - range0 );
		const auto doubleRange0 = ( range0 * 2.f );

		return anchors[ 0 ] + ( doubleRange0 * _t ) + ( range2 * ( _t * _t ) );
	}
	auto PlotCubic( float _t )const noexcept
	{
		const auto range10 = anchors[ 1 ] - anchors[ 0 ];
		const auto range21 = anchors[ 2 ] - anchors[ 1 ];
		const auto range32 = anchors[ 3 ] - anchors[ 2 ];

		//( ( p2 - p1 ) - ( p1 - p0 ) )
		const auto range2110 = range21 - range10;

		//( ( p3 - p2 ) - ( p2 - p1 ) )
		const auto range3221 = range32 - range21;

		//( p1 - p0 ) * 3.f
		const auto range10x3 = range10 * 3.f;

		//( ( p2 - p1 ) - ( p1 - p0 ) ) * 3.f
		const auto range2110x3 = range2110 * 3.f;

		//( ( p3 - p2 ) - ( p2 - p1 ) ) - ( ( p2 - p1 ) - ( p1 - p0 ) )
		const auto range3221_2110 = range3221 - range2110;

		const auto t2 = _t * _t;
		const auto t3 = _t * _t * _t;

		return ( anchors[ 0 ] + ( range10x3 * _t ) + ( range2110x3 * t2 ) + ( range3221_2110 * t3 ) );
	}
	auto PlotUknown( float _t )const noexcept
	{
		const float it = 1.f - _t;

		auto lerp = [ = ]( const auto& p0, const auto& p1 ) { return ( ( p0 * it ) + ( p1 * _t ) ); };

		std::vector<T> results;
		results.reserve( anchors.Count() );

		// First round, use anchors as source
		for( int i = 0, j = 1; j < anchors.Count(); ++i, ++j )
		{
			results.push_back( lerp( anchors[ i ], anchors[ j ] ) );
		}

		// Remaining rounds, just overwrite results vector, 
		// popping last element off each pass until only one remains
		while( results.size() > std::size_t( 1 ) )
		{
			for( int i = 0, j = 1; j < results.size(); ++i, ++j )
			{
				results[ i ] = lerp( results[ i ], results[ j ] );
			}

			results.pop_back();
		}

		return results.front();
	}

private:
	AnchorPoints<T> anchors;
	std::vector<T> points;
	std::uint32_t sections = 1u;
};

template<typename T> AnchorPoints( std::initializer_list<T> )->AnchorPoints<T>;
template<typename T> Bezier( AnchorPoints<T> )->Bezier<T>;

template<typename T>
Bezier<T> plot_curve( std::vector<T> source, int output_element_count )
{
	return { size_t( output_element_count ), AnchorPoints<T>( std::move( source ) ) };
}

#include <cassert>
#include <memory>
template<typename T>
class aligned_ptr
{
public:
	aligned_ptr() = default;
	template<typename...Args>
	aligned_ptr( size_t alignment, Args&&... args )noexcept( std::is_nothrow_constructible_v<T> )
		:
		ptr( reinterpret_cast< T* >( _aligned_malloc( sizeof( T ), alignment ) ) )
	{
		new ( ptr ) T{ std::forward<Args>( args )... };
	}
	aligned_ptr( aligned_ptr const& ) = delete;
	aligned_ptr( aligned_ptr&& ) = default;

	aligned_ptr& operator=( aligned_ptr const& ) = delete;
	aligned_ptr& operator=( aligned_ptr&& ) = default;

	~aligned_ptr()noexcept { _aligned_free( ptr ); }

	T& operator*()noexcept { return *ptr; }
	T const& operator*()const noexcept { return *ptr; }

	T* operator->()noexcept { return ptr; }
	T const* operator->()const noexcept { return ptr; }

	T* get()noexcept { return ptr; }
	T const* get()const noexcept { return ptr; }

private:
	T* ptr = nullptr;
};

template<typename T>
class aligned_ptr<T[]>
{
public:
	aligned_ptr() = default;
	aligned_ptr( size_t count_, size_t alignment_ )noexcept( std::is_nothrow_constructible_v<T> )
		:
		m_ptr( reinterpret_cast< T* >( _aligned_malloc( sizeof( T ) * count_, alignment_ ) ) ),
		m_count( count_ )
	{
		for( int i = 0; i < count_; ++i )
		{
			T* ptr = std::addressof( m_ptr[ i ] );
			new ( ptr ) T{};
		}
	}
	~aligned_ptr()noexcept
	{
		_aligned_free( m_ptr );
	}
	aligned_ptr( aligned_ptr const& ) = delete;
	aligned_ptr( aligned_ptr&& ) = default;
	
	aligned_ptr& operator=( aligned_ptr const& ) = delete;
	aligned_ptr& operator=( aligned_ptr&& ) = default;

	T& operator[]( size_t index_ )noexcept
	{
		assert( index_ < m_count );
		return m_ptr[ index_ ];
	}
	T const& operator[]( size_t index_ )const noexcept
	{
		assert( index_ < m_count );
		return m_ptr[ index_ ];
	}
	T* get()noexcept { return m_ptr; }
	T const* get()const noexcept { return m_ptr; }
	size_t count()const noexcept { return m_count; }

private:
	T* m_ptr = nullptr;
	size_t m_count = 0;
};