#include "Button.h"
#include "ButtonController.h"

void sns::ButtonController::Select( Button & model ) noexcept
{
	model.color = Button::selected_color;
}

void sns::ButtonController::Deselect( Button & model ) noexcept
{
	model.color = Button::deselected_color;
}
