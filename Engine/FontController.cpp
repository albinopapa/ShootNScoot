#include "Font.h"
#include "FontController.h"
#include "RectController.h"

int FontController::GlyphWidth( Font const & model ) noexcept
{
	return int( RectController::Width( model.glyph_rect ) );
}

int FontController::GlyphHeight( Font const & model ) noexcept
{
	return int( RectController::Height( model.glyph_rect ) );
}
