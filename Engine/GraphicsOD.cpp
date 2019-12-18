#define GOD_GRAPHICS
#include "Graphics.h"
#include "SpriteEffect.h"

void dummy( Graphics& gfx )
{
	gfx.DrawSprite( 0,0,RectI{ 0,0,0,0 },RectI{ 0,0,0,0 },Surface{},SpriteEffect::Copy{} );
	gfx.DrawSprite( 0,0,RectI{ 0,0,0,0 },RectI{ 0,0,0,0 },Surface{},SpriteEffect::Chroma{ Colors::Black } );
	gfx.DrawSprite( 0,0,RectI{ 0,0,0,0 },RectI{ 0,0,0,0 },Surface{},SpriteEffect::Substitution{ Colors::Black,Colors::Black } );
}
