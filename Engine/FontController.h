#pragma once

class Font;

class FontController
{
public:
	static int GlyphWidth( Font const& model )noexcept;
	static int GlyphHeight( Font const& model )noexcept;
};