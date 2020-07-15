#include "Enemies.h"

void Enemy::Update( float dt )
{
	std::visit( [ & ]( auto& enemy_ ){ enemy_.Update( *this, dt ); }, variant );
}

void Enemy1::Update( Enemy& parent, float dt )
{
	parent.position += ( parent.velocity * ( speed * dt ) );
}
void Enemy2::Update( Enemy& parent, float dt )
{
	parent.position += ( parent.velocity * ( speed * dt ) );
}
void Enemy3::Update( Enemy& parent, float dt )
{
	parent.position += ( parent.velocity * ( speed * dt ) );
}
void Enemy4::Update( Enemy& parent, float dt )
{
	parent.position += ( parent.velocity * ( speed * dt ) );
}
void Enemy5::Update( Enemy& parent, float dt )
{
	parent.position += ( parent.velocity * ( speed * dt ) );
}
