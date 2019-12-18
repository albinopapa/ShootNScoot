#include "Shield.h"
namespace sns
{
	void Shield::Update( float delta_time ) noexcept
	{
		switch( state )
		{
			case State::Recharging:
				health += ( delta_time * Shield::recharge_rate );
				if( health >= Shield::recharge_max )
				{
					state = State::Full;
					health = Shield::recharge_max;
				}
				break;
			case State::Depleted:
				recharge_delay_timer -= delta_time;
				if( recharge_delay_timer <= 0.f )
				{
					state = State::Recharging;
					recharge_delay_timer = Shield::recharge_delay;
				}
				break;
		}
	}
	void Shield::TakeDamage( float amount ) noexcept
	{
		switch( state )
		{
			case State::Full:
			case State::Recharging:
			{
				health -= amount;
				if( health <= 0.f )
				{
					health = 0.f;
					state = State::Depleted;
				}
				else if( health < Shield::recharge_max )
				{
					state = State::Recharging;
				}
			}
		}
	}
	void Shield::Draw( Vec2 const& center, Graphics & gfx ) const noexcept
	{
		switch( state )
		{
			case State::Full:
			case State::Recharging:
			{
				constexpr auto sqrRadius = sqr( Shield::radius );

				const auto t = ( 255.f * ( health / Shield::recharge_max ) );
				const auto r = uint8_t( 255.f - t );
				const auto g = uint8_t( t );
				const auto b = uint8_t( 0 );

				const auto xStart = std::max( -( center.x - Shield::radius ), 0.f );
				const auto yStart = std::max( -( center.y - Shield::radius ), 0.f );
				const auto xEnd = std::min( Graphics::ScreenWidth - ( center.x - Shield::radius ), Shield::radius * 2.f );
				const auto yEnd = std::min( Graphics::ScreenHeight - ( center.y - Shield::radius ), Shield::radius * 2.f );

				for( float y = yStart - Shield::radius; y < yEnd - Shield::radius; ++y )
				{
					for( float x = xStart - Shield::radius; x < xEnd - Shield::radius; ++x )
					{
						const auto sqrDist = sqr( x ) + sqr( y );
						if( sqrDist <= sqrRadius )
						{
							const auto position = Vei2( int( center.x + x ), int( center.y + y ) );
							const auto a = ( uint8_t( ( sqrDist * 255 ) / sqrRadius ) );
							const auto color = AlphaBlend( Color( a, r, g, b ), gfx.GetPixel( position.x, position.y ) );
							gfx.PutPixel( position.x, position.y, color );
						}
					}
				}
				break;
			}
		}
	}
	void Shield::Reset() noexcept
	{
		health = 100.f;
		state = State::Full;
		recharge_delay_timer = 0.f;
	}
	RectF Shield::AABB( Vec2 position ) const noexcept
	{
		return RectF{ -radius, -radius, radius, radius } + position;
	}
}
