#include "ColorKeyTextureEffect.h"
#include "Font.h"
#include "Pipeline.h"
#include "PointSampler.h"
#include "RasterStates.h"
#include "SpriteEffect.h"

#include <cassert>

using FontEffect = ColorKeyTextureEffect<PointSampler>;

Font::Font( const std::string& filename )
{
	auto make_temp_sprite = [ this ]( Surface const& font_sheet, char ch )
	{
		assert( ch >= firstChar && ch <= lastChar );
		// font sheet glyphs start at ' ', calculate index into sheet
		const int glyphIndex = ch - ' ';

		// map 1d glyphIndex to 2D coordinates
		const int yGlyph = glyphIndex / nColumns;
		const int xGlyph = glyphIndex % nColumns;

		// convert the sheet grid coords to pixel coords in sheet
		const auto sheetRect = RectI(
			Vei2{ xGlyph * int( glyph_rect.Width() ), yGlyph * int( glyph_rect.Height() ) },
			SizeI{ int( glyph_rect.Width() ), int( glyph_rect.Height() ) }
		);

		auto temp = Surface{ sheetRect.Width(), sheetRect.Height() };

		for( int y = 0; y < temp.GetHeight(); ++y )
		{
			for( int x = 0; x < temp.GetWidth(); ++x )
			{
				if( font_sheet.GetPixel( sheetRect.left + x, sheetRect.top + y ) == Colors::Black )
					temp.PutPixel( x, y, Colors::White );
				else
					temp.PutPixel( x, y, Colors::Magenta );
			}
		}

		return temp;
	};

	// holds the font sheet bitmap data
	auto surface = Surface{ filename };

	const auto glyphWidth = surface.GetWidth() / nColumns;
	const auto glyphHeight = surface.GetHeight() / nRows;

	// verify that bitmap had valid dimensions
	assert( glyphWidth * nColumns == surface.GetWidth() );
	assert( glyphHeight * nRows == surface.GetHeight() );

	// calculate glyph dimensions from bitmap dimensions
	glyph_rect = RectF(
		( -Vec2{ float( glyphWidth ),float( glyphHeight ) } ) * .5f,
		SizeF{ float( glyphWidth ),float( glyphHeight ) }
	);

	char ch = firstChar;
	for( auto& glyph : glyphs )
	{
		if( ch > lastChar ) break;
		glyph = make_temp_sprite( surface, ch++ );
	}

}

void Font::DrawText( const std::string& text, const Vei2& pos, Color color, Graphics& gfx )const
{
	// curPos is the pos that we are drawing to on the screen
	auto curPos = pos;
	for( auto c : text )
	{
		// only draw characters that are on the font sheet
		// start at firstChar + 1 because might as well skip ' ' as well
		// on a newline character, reset x position and move down by 1 glyph height
		if( c >= firstChar + 1 && c <= lastChar )
		{
			const auto index = c - ' ';
			auto pl = Pipeline{ FontEffect{}, gfx };
			pl.PSSetTexture( glyphs[ index ] );
			pl.PSSetConstantBuffer( { Colors::Magenta, color } );
			pl.vertices[ 0 ] = { { -.5f, -.5f }, { 0.f, 0.f } };
			pl.vertices[ 1 ] = { {  .5f, -.5f }, { 1.f, 0.f } };
			pl.vertices[ 2 ] = { { -.5f,  .5f }, { 0.f, 1.f } };
			pl.vertices[ 3 ] = { {  .5f,  .5f }, { 1.f, 1.f } };
			pl.Draw( glyph_rect + Vec2( curPos ), Radian{} );
			/*gfx.DrawSprite( 
				RectI( glyph_rect ) + curPos, 
				glyphs[ index ],  
				SpriteEffect::TintWithChroma{ color, Colors::Magenta }
				);*/
		}
		else if( c == '\n' )
		{
			// carriage return
			curPos.x = pos.x;
			
			// line feed
			curPos.y += int( glyph_rect.Height() );

			// we don't want to advance the character position right for a newline
			continue;
		}
		else if( c == '\t' )
		{
			curPos.x += int( glyph_rect.Width() * 4.f );
		}

		// advance screen pos for next character
		curPos.x += int( glyph_rect.Width() );
	}
}

int Font::GlyphWidth() const noexcept
{
	return int( glyph_rect.Width() );
}

int Font::GlyphHeight() const noexcept
{
	return int( glyph_rect.Height() );
}
