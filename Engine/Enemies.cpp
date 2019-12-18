#include "Enemies.h"

void sns::Enemy::Update( float dt )
{
	auto do_update = [&](auto& entity_)
	{
		using type = std::decay_t<decltype( entity_ )>;
		const auto delta = type::waypoints[ waypoint_index ] - position;

		velocity = delta.Normalize();
		position += ( velocity * ( type::speed * dt ) );

		const auto sqrDistToWaypoint = delta.LengthSq();
		constexpr auto minSqrDistFromWaypoint = sqr( type::aabb.Width() / 2.f );

		if( sqrDistToWaypoint < minSqrDistFromWaypoint ) ++waypoint_index;

		if( waypoint_index >= type::waypoints.size() ) health = 0.f;
	};

	std::visit( do_update, variant );
}

void sns::Enemy::TakeDamage( float amount ) noexcept
{
	health -= amount;
}

void sns::Enemy::Draw( Surface const & sprite, Graphics & gfx ) const noexcept
{
	auto do_draw = [&](auto const& entity_)
	{
		using type = std::decay_t<decltype( entity_ )>;

		const auto shipRect = RectI( type::aabb + position );
		gfx.DrawSprite(
			shipRect.left,
			shipRect.top,
			sprite,
			SpriteEffect::Chroma{ Colors::Magenta }
		);
	};

	std::visit( do_draw, variant );
}

RectF sns::Enemy::AABB() const noexcept
{
	return std::visit( [ & ]( auto const& enemy_ )
	{
		using type = std::decay_t<decltype( enemy_ )>;
		return type::aabb + position;
	}, variant );
}

float sns::Enemy::Damage() const noexcept
{
	return std::visit( [ & ]( auto const& enemy_ ) {
		using type = std::decay_t<decltype( enemy_ )>;
		return type::damage;
	}, variant );
}
