#include "Bullet.h"
#include "ChiliMath.h"
#include <algorithm>

namespace sns
{
	void Bullet::DrawEffect( float x, float y, Vec2 const & position, Graphics & gfx ) noexcept
	{
		gfx.PutPixel(
			int( x + position.x ),
			int( y + position.y ),
			color
		);
	}

	void PlasmaBall::DrawEffect( float x, float y, Vec2 const & position, Graphics & gfx ) noexcept
	{
		constexpr auto radius = aabb.Width() * .5f;
		constexpr auto sqrRadius = sqr( radius );

		const auto ix = x;
		const auto iy = y;

		const auto sqrDist = sqr( ix ) + sqr( iy );
		if( sqrDist < sqrRadius )
		{
			const auto px = int( ix + position.x );
			const auto py = int( iy + position.y );
			
			const auto alpha = uint8_t( 255.f * ( 1.f - ( sqrDist / sqrRadius ) ) );
			const auto bgcolor = gfx.GetPixel( px, py );
			const auto glow = AlphaBlend( Color( Colors::White, alpha ), color );
			const auto clr = AlphaBlend( Color( glow, alpha ), bgcolor );

			gfx.PutPixel( px, py, clr );
		}
	}

	void Missile::DrawEffect( float x, float y, Vec2 const & position, Graphics & gfx ) noexcept
	{
		gfx.PutPixel(
			int( x + position.x ),
			int( y + position.y ),
			color
		);
	}

	void Ammo::Update( float delta_time ) noexcept
	{
		std::visit( [ & ]( const auto& ammo_ ) {
			using type = std::decay_t<decltype( ammo_ )>;
			position += ( velocity * ( type::speed * delta_time ) );
			isAlive = Graphics::IsVisible( RectI( type::aabb + position ) ) && energy > 0.f;
		}, variant );
	}
	void Ammo::TakeDamage( float amount ) noexcept
	{
		energy -= amount;
		energy = std::max( energy, 0.f );
	}
	float Ammo::Damage() const noexcept
	{
		return std::visit( [ & ]( const auto& ammo_ ) {
			using type = std::decay_t<decltype( ammo_ )>;
			return type::damage * ( energy / type::max_energy );
		}, variant );
	}
	RectF Ammo::AABB() const noexcept
	{
		return std::visit( [ & ]( const auto& ammo ) {
			return std::decay_t<decltype( ammo )>::aabb + position;
		}, variant );
	}
	void Ammo::Draw( Graphics & gfx ) const noexcept
	{
		std::visit( [ & ]( const auto& ammo_ ) {
			using type = std::decay_t<decltype( ammo_ )>;
			constexpr auto half_width = type::aabb.Width() * .5f;
			constexpr auto half_height = type::aabb.Height() * .5f;

			const auto tborder = type::aabb + position;

			const auto xStart = std::max( 0.f, -tborder.left ) - half_width;
			const auto yStart = std::max( 0.f, -tborder.top ) - half_height;
			const auto xEnd = std::min( float( Graphics::ScreenWidth ) - tborder.left, type::aabb.Width() ) - half_width;
			const auto yEnd = std::min( float( Graphics::ScreenHeight ) - tborder.top, type::aabb.Height() ) - half_height;

			for( float y = yStart; y < yEnd; ++y )
			{
				for( float x = xStart; x < xEnd; ++x )
				{
					type::DrawEffect( x, y, position, gfx );
				}
			}
		}, variant );
	}
}
