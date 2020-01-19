#include "Font.h"
#include "RectController.h"
#include "SurfaceController.h"
#include <cassert>

Font::Font( const std::string& filename )
{
	auto map_glyph_rect = []( int glyph_width, int glyph_height, char ch )
	{
		assert( ch >= firstChar && ch <= lastChar );
		// font sheet glyphs start at ' ', calculate index into sheet
		const int glyphIndex = ch - ' ';

		// map 1d glyphIndex to 2D coordinates
		const int xGlyph = ( glyphIndex % nColumns ) * glyph_width;
		const int yGlyph = ( glyphIndex / nColumns ) * glyph_height;

		// convert the sheet grid coords to pixel coords in sheet
		return RectI( Vei2{ xGlyph, yGlyph }, SizeI{ glyph_width, glyph_height } );
	};
	auto make_glyph_sprite = [ & ]( Surface const& font_sheet, char ch )
	{
		const auto sheetRect = map_glyph_rect(
			int( RectController::Width( glyph_rect ) ),
			int( RectController::Height( glyph_rect ) ),
			ch 
		);

		auto temp = SurfaceController::CreateSurface(
			RectController::Width( sheetRect ),
			RectController::Height( sheetRect )
		);

		for( int y = 0; y < SurfaceController::GetHeight( temp ); ++y )
		{
			for( int x = 0; x < SurfaceController::GetWidth( temp ); ++x )
			{
				if( SurfaceController::GetPixel( font_sheet, { sheetRect.left + x, sheetRect.top + y } ) == Colors::Black )
					SurfaceController::PutPixel( temp, { x, y }, Colors::White );
				else
					SurfaceController::PutPixel( temp, { x, y }, Colors::Magenta );
			}
		}

		return temp;
	};

	// holds the font sheet bitmap data
	auto surface = SurfaceController::CreateSurface( filename );

	const auto glyphWidth  = SurfaceController::GetWidth( surface ) / nColumns;
	const auto glyphHeight = SurfaceController::GetHeight( surface ) / nRows;

	// verify that bitmap had valid dimensions
	assert( glyphWidth * nColumns == SurfaceController::GetWidth( surface ) );
	assert( glyphHeight * nRows == SurfaceController::GetHeight( surface ) );

	// calculate glyph dimensions from bitmap dimensions
	glyph_rect = RectF(
		( -Vec2{ float( glyphWidth ),float( glyphHeight ) } ) * .5f,
		SizeF{ float( glyphWidth ),float( glyphHeight ) }
	);

	char ch = firstChar;
	for( auto& glyph : glyphs )
	{
		if( ch > lastChar ) break;
		glyph = make_glyph_sprite( surface, ch++ );
	}
}
