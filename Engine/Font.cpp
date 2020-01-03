#include "Font.h"
#include <cassert>
#include "SpriteEffect.h"

Font::Font( const std::string& filename, Color chroma )
	:
	surface( filename ),
	// calculate glyph dimensions from bitmap dimensions
	glyphWidth( surface.GetWidth() / nColumns ),
	glyphHeight( surface.GetHeight() / nRows ),
	chroma( chroma )
{
	// verify that bitmap had valid dimensions
	assert( glyphWidth * nColumns == surface.GetWidth() );
	assert( glyphHeight * nRows == surface.GetHeight() );
}

void Font::DrawText( const std::string& text,const Vei2& pos,Color color,Graphics& gfx ) const
{
	// Make pipeline compatible temp glyph sprite
	auto make_temp_sprite = [ & ]( RectI const& sheetRect )
	{
		auto temp = Surface{ glyphWidth, glyphHeight };

		for( int y = 0; y < temp.GetHeight(); ++y )
		{
			for( int x = 0; x < temp.GetWidth(); ++x )
			{
				if( surface.GetPixel( sheetRect.left + x, sheetRect.top + y ) == Colors::Black )
					temp.PutPixel( x, y, Colors::White );
				else
					temp.PutPixel( x, y, Colors::Magenta );
			}
		}

		return temp;
	};

	const auto glyph_rect = RectF(
		-Vec2{ float( glyphWidth / 2 ),float( glyphHeight / 2 ) },
		SizeF{ float( glyphWidth ),float( glyphHeight ) }
	);

	// curPos is the pos that we are drawing to on the screen
	auto curPos = pos;
	for( auto c : text )
	{
		// on a newline character, reset x position and move down by 1 glyph height
		if( c == '\n' )
		{
			// carriage return
			curPos.x = pos.x;
			// line feed
			curPos.y += glyphHeight;
			// we don't want to advance the character position right for a newline
			continue;
		}
		// only draw characters that are on the font sheet
		// start at firstChar + 1 because might as well skip ' ' as well
		else if( c >= firstChar + 1 && c <= lastChar )
		{
			const auto sheetRect = MapGlyphRect( c );

			const auto rect = glyph_rect + Vec2( float( curPos.x ), float( curPos.y ) );

			// Temporary sprite to be compatible with pipeline
			const auto glyph_sprite = make_temp_sprite( sheetRect );

			gfx.DrawSprite( rect, Radian{ 0.f }, glyph_sprite, color );
		}
		// advance screen pos for next character
		curPos.x += glyphWidth;
	}
}

RectI Font::MapGlyphRect( char c ) const
{
	assert( c >= firstChar && c <= lastChar );
	// font sheet glyphs start at ' ', calculate index into sheet
	const int glyphIndex = c - ' ';
	// map 1d glyphIndex to 2D coordinates
	const int yGlyph = glyphIndex / nColumns;
	const int xGlyph = glyphIndex % nColumns;
	// convert the sheet grid coords to pixel coords in sheet
	return RectI(
		Vei2{ xGlyph * glyphWidth, yGlyph * glyphHeight },
		SizeI{ glyphWidth, glyphHeight }
	);
}
