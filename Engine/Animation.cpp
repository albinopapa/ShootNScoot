#include "Animation.h"
#include "SpriteEffect.h"

Animation::Animation( int x,int y,int width,int height,int count,
					  const Surface& sprite,float holdTime,Color chroma )
	:
	sprite( sprite ),
	holdTime( holdTime ),
	chroma( chroma )
{
	for( int i = 0; i < count; i++ )
	{
		frames.emplace_back( x + i * width,x + (i + 1) * width,y,y + height );
	}
}

void Animation::Draw( const Vec2& pos, Graphics& gfx, Color tint )const noexcept
{
	//gfx.DrawSprite( RectF( frames[ iCurFrame ] ) + pos, Radian{ 0.f }, sprite, tint );
}

void Animation::Update( float dt )
{
	curFrameTime += dt;
	while( curFrameTime >= holdTime )
	{
		Advance();
		curFrameTime -= holdTime;
	}
}

void Animation::Advance()
{
	iCurFrame = int( std::size_t( iCurFrame + 1 ) % frames.size() );
}
