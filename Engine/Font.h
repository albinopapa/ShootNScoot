#pragma once

#include "Graphics.h"
#include "Surface.h"
#include "Vec2.h"

#include <vector>

class Font
{
public:
	Font( const std::string& filename );
	void DrawText( const std::string& text, const Vei2& pos, Color color, Graphics& gfx )const;
	int GlyphWidth()const noexcept;
	int GlyphHeight()const noexcept;
private:
	std::vector<Surface> glyphs = std::vector<Surface>{ 96 };

	// this gives the dimensions of a glyph in the font sheet
	RectF glyph_rect;

	// number of rows / columns in the font sheet (this is fixed)
	static constexpr int nColumns = 32;
	static constexpr int nRows = 3;

	// start and end drawable character codes
	static constexpr char firstChar = ' ';
	static constexpr char lastChar = '~';
};