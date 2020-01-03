#include "Bullet.h"
#include "ChiliMath.h"
#include <algorithm>

namespace sns
{
	Surface make_bullet_sprite() {
		auto sprite = Surface{ int( Bullet::aabb.Width() ), int( Bullet::aabb.Height() ) };

		sprite.Fill( Bullet::color );

		return sprite;
	}
	Surface make_plasma_ball_sprite() {
		auto sprite = Surface{ int( PlasmaBall::aabb.Width() ), int( PlasmaBall::aabb.Height() ) };

		constexpr auto radius = PlasmaBall::aabb.Width() * .5f;
		constexpr auto sqrRadius = sqr( radius );

		for( int y = -radius; y < radius; ++y )
		{
			for( int x = -radius; x < radius; ++x )
			{
				const auto sqrDist = sqr( x ) + sqr( y );
				if( sqrDist < sqrRadius )
				{
					const auto alpha = uint8_t( 255.f * ( 1.f - ( sqrDist / sqrRadius ) ) );
					const auto glow = AlphaBlend( Color( Colors::White, alpha ), PlasmaBall::color);

					sprite.PutPixel( x + radius, y + radius, Color( glow, alpha ) );
				}
			}
		}

		return sprite;
	}
	Surface make_missile_sprite() {
		auto sprite = Surface{ int( Missile::aabb.Width() ), int( Missile::aabb.Height() ) };

		for( int y = 0; y < sprite.GetHeight(); ++y )
		{
			for( int x = 0; x < sprite.GetWidth(); ++x )
			{
				sprite.PutPixel( x, y, Missile::color );
			}
		}

		return sprite;
	}

	const Surface Bullet::sprite = make_bullet_sprite();
	const Surface PlasmaBall::sprite = make_plasma_ball_sprite();
	const Surface Missile::sprite = make_missile_sprite();

	void Ammo::Update( float delta_time ) noexcept
	{
		std::visit( [ & ]( const auto& ammo_ ) {
			using type = std::decay_t<decltype( ammo_ )>;
			position += ( velocity * ( type::speed * delta_time ) );
		}, variant );
	}
}
