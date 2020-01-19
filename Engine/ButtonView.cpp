#include "ButtonView.h"
#include "Font.h"
#include "FontView.h"
#include "Menus.h"

void sns::ButtonView::Draw( Button const& model, Font const& font, Surface& render_target )noexcept
{
	FontView::Draw( font, model.label, model.position, model.color, render_target );
}
