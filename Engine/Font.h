#pragma once

#include "Surface.h"

#include <string>
#include <vector>

class Font
{
public:
	Font( const std::string& filename );
private:
	friend class FontController;
	friend class FontView;

	// number of rows / columns in the font sheet (this is fixed)
	static constexpr int nColumns = 32;
	static constexpr int nRows = 3;

	std::vector<Surface> glyphs = std::vector<Surface>{ nColumns * nRows };

	// this gives the dimensions of a glyph in the font sheet
	RectF glyph_rect;

	// start and end drawable character codes
	static constexpr char firstChar = ' ';
	static constexpr char lastChar = '~';
};