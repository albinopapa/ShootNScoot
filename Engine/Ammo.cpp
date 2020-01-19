#include "Ammo.h"
#include "ChiliMath.h"
#include "ColorController.h"
#include "RectController.h"
#include "SurfaceController.h"
#include <algorithm>
#include <type_traits>

namespace sns
{
	Surface make_bullet_sprite() {
		auto sprite = SurfaceController::CreateSurface( 
			int( RectController::Width( Bullet::aabb ) ), 
			int( RectController::Height( Bullet::aabb ) ) 
		);

		SurfaceController::Fill( sprite, Bullet::color );

		return sprite;
	}
	Surface make_plasma_ball_sprite() {
		auto sprite = SurfaceController::CreateSurface(
			int( RectController::Width( PlasmaBall::aabb ) ),
			int( RectController::Height( PlasmaBall::aabb ) )
		);

		constexpr auto radius = int( RectController::Width( PlasmaBall::aabb ) * .5f );
		constexpr auto sqrRadius = sqr( radius );

		for( int y = -radius; y < radius; ++y )
		{
			for( int x = -radius; x < radius; ++x )
			{
				const auto sqrDist = sqr( x ) + sqr( y );
				if( sqrDist < sqrRadius )
				{
					const auto alpha = uint8_t( 255.f * ( 1.f - ( float( sqrDist ) / float( sqrRadius ) ) ) );
					const auto glow = ColorController::AlphaBlend( Color( Colors::White, alpha ), PlasmaBall::color);
					
					SurfaceController::PutPixel( sprite, { x + radius, y + radius }, Color( glow, alpha ) );
				}
			}
		}

		return sprite;
	}
	Surface make_missile_sprite() {
		auto sprite = SurfaceController::CreateSurface(
			int( RectController::Width( Missile::aabb ) ),
			int( RectController::Height( Missile::aabb ) )
		);

		for( int y = 0; y < SurfaceController::GetHeight( sprite ); ++y )
		{
			for( int x = 0; x < SurfaceController::GetWidth( sprite ); ++x )
			{
				SurfaceController::PutPixel( sprite, { x, y }, Missile::color );
			}
		}

		return sprite;
	}

	const Surface Bullet::sprite = make_bullet_sprite();
	const Surface PlasmaBall::sprite = make_plasma_ball_sprite();
	const Surface Missile::sprite = make_missile_sprite();

	Ammo::Ammo( Vec2 const & position_, Vec2 const & direction_, Ammo::Owner owner_, AmmoType type )
		:
		position( position_ ),
		velocity( direction_ ),
		owner( owner_ ),
		variant( type )
	{
		std::visit( [ & ]( auto& ammo )
		{
			using type = std::decay_t<decltype( ammo )>;
			energy = type::max_energy;
		}, type );
	}
}
