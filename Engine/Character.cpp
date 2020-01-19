#include "Character.h"

Character::Character( const Vec2& pos )
	:
	pos( pos )
{
	for( int i = 0; i < (int)Sequence::StandingLeft; i++ )
	{
		animations.emplace_back( Animation( 90,90 * i,90,90,4,sprite,0.16f ) );
	}
	for( int i = (int)Sequence::StandingLeft; i < (int)Sequence::Count; i++ )
	{
		animations.emplace_back( Animation( 0,90 * (i-(int)Sequence::StandingLeft),90,90,1,sprite,0.16f ) );
	}
}
