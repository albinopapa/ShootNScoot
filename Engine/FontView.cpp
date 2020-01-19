#include "EffectController.h"
#include "EffectView.h"
#include "Font.h"
#include "FontView.h"
#include "SurfaceController.h"

FontView::Effect FontView::effect;

void FontView::Draw( Font const& model, const std::string& text, Vec2 const& pos, Color color, Surface& render_target )noexcept
{
	const auto glyph_size = SizeF{
		RectController::Width( model.glyph_rect ),
		RectController::Height( model.glyph_rect )
	};

	// tPos is the adjusted position to work with the render pipeline
	const auto surface_rect = SurfaceController::GetRect( render_target );
	const auto offset = Vec2( surface_rect.left, surface_rect.top );
	const auto tPos = pos + offset;

	// curPos is the cursor position
	auto cursor = Point{ 0, 0 };

	for( auto c : text )
	{
		// only draw characters that are on the font sheet
		if( c >= Font::firstChar && c <= Font::lastChar )
		{
			// start at firstChar + 1 because might as well skip ' ' as well
			if( c > Font::firstChar )
			{
				const auto index = c - ' ';

				const auto curPos = tPos + ( Vec2( cursor ) * glyph_size );
				EffectController::PSSetConstantBuffer( effect, { Colors::Magenta, color } );
				EffectController::PSSetTexture( effect, model.glyphs[ index ] );
				EffectController::VSSetConstantBuffer( effect, {
						Mat3F::Rotate( Radian{ 0.f } ) *
						Mat3F::Scale( glyph_size ) *
						Mat3F::Translation( curPos )
					} );
				EffectController::VSSetVertexBuffer( effect, vertices );

				EffectView::Draw( effect, render_target );
			}

			// advance screen pos for next character
			++cursor.x;
		}
		else
		{
			// on a newline character, reset x position and move down by 1 glyph height
			// on a tab character, move x position over 4 spaces
			if( c == '\n' )
			{
				cursor = { 0, cursor.y + 1 };
			}
			else if( c == '\t' )
			{
				cursor = { cursor.x + 4, cursor.y };
			}
		}
	}
}
