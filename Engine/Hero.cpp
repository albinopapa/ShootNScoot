#include "Hero.h"
#include "World.h"

namespace sns
{
	Hero::Hero()noexcept
	{
		weapon.variant = Gun{};
	}
	void Hero::Update( Keyboard& kbd, float dt, World& world )
	{
		Vec2 direction = { 0.f, 0.f };
		if( kbd.KeyIsPressed( VK_UP ) )
		{
			direction.y = -1.f;
		}
		else if( kbd.KeyIsPressed( VK_DOWN ) )
		{
			direction.y = 1.f;
		}

		if( kbd.KeyIsPressed( VK_LEFT ) )
		{
			direction.x = -1.f;
		}
		else if( kbd.KeyIsPressed( VK_RIGHT ) )
		{
			direction.x = 1.f;
		}

		if( kbd.KeyIsPressed( '1' ) )
		{
			if( !std::holds_alternative<Gun>( weapon.variant ) )
				weapon.variant = Gun{};
		}
		else if( kbd.KeyIsPressed( '2' ) )
		{
			if( !std::holds_alternative<MachineGun>( weapon.variant ) )
				weapon.variant = MachineGun{};
		}
		else if( kbd.KeyIsPressed( '3' ) )
		{
			if( !std::holds_alternative<PlasmaGun>( weapon.variant ) )
				weapon.variant = PlasmaGun{};
		}

		velocity = direction.Normalize();
		position += ( velocity * ( Hero::max_speed * dt ) );

		const auto heroRect = Hero::aabb + position;
		if( !heroRect.IsContainedBy( screenRect ) )
		{
			position.x = std::clamp(
				position.x,
				screenRect.left + Hero::aabb.right,
				screenRect.right + Hero::aabb.left
			);
			position.y = std::clamp(
				position.y,
				screenRect.top + Hero::aabb.bottom,
				screenRect.bottom + Hero::aabb.top
			);
		}

		weapon.Update( dt );
		if( kbd.KeyIsPressed( VK_CONTROL ) && weapon.CanFire() )
		{
			weapon.Fire( position, Vec2{ 0.f, -1.f }, world );
		}

		shield.Update( dt );
	}
	
	void Hero::TakeDamage( float amount )noexcept
	{
		if( shield.health > 0.f )
			shield.TakeDamage( amount );
		else
			health -= amount;

		health = std::max( health, 0.f );
	}

	void Hero::Draw( Surface const& sprite, Graphics& gfx )const noexcept
	{
		shield.Draw( position, gfx );

		const auto shipRect = RectI( Hero::aabb + position );

		gfx.DrawSprite(
			shipRect.left,
			shipRect.top,
			sprite,
			SpriteEffect::Chroma{ Colors::Magenta }
		);

	}
	void Hero::Reset() noexcept
	{
		weapon.Reset();
		shield.Reset();
		health = 100.f;
		velocity = { 0.f, 0.f };
		position = screenRect.Center();
	}
	RectF Hero::AABB() const noexcept
	{
		return Hero::aabb + position;
	}
}