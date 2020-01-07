#include "Shield.h"
#include "ChiliMath.h"

namespace sns
{
	const Surface Shield::sprite = Shield::MakeSprite();

	void Shield::Update( float delta_time ) noexcept
	{
		switch( state )
		{
			case ShieldState::Recharging:
				health += ( delta_time * Shield::recharge_rate );
				break;
			case ShieldState::Depleted:
				recharge_delay_timer -= delta_time;
				break;
		}
	}
	float Shield::Radius() const noexcept
	{
		return radius;
	}
	float Shield::Health() const noexcept
	{
		return health;
	}
	void Shield::Reset() noexcept
	{
		health = 100.f;
		state = ShieldState::Full;
		recharge_delay_timer = 0.f;
	}
	Surface Shield::MakeSprite()
	{
		constexpr auto iRadius = int( radius );
		auto sprite = Surface( iRadius * 2, iRadius * 2 );
		constexpr auto sqrRadius = sqr( iRadius );

		for( int y = -iRadius; y < iRadius; ++y )
		{
			for( int x = -iRadius; x < iRadius; ++x )
			{
				const auto sqrDist = sqr( x ) + sqr( y );

				const auto alpha = sqrDist < sqrRadius ?
					uint8_t( ( sqrDist * 255 ) / sqrRadius ) : 0;

				const auto color = ( sqrDist < sqrRadius ) ?
					Color( Colors::White, alpha ) : Colors::Magenta;

				sprite.PutPixel( x + radius, y + radius, color );
			}
		}

		return sprite;
	}
}
