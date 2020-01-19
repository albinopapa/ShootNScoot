#include "AppController.h"
#include "ButtonController.h"
#include "Menus.h"
#include "MenuController.h"
#include "GameController.h"

int sns::MenuController::Choice( Menu const & model ) noexcept
{
	return model.choice;
}

void sns::MenuController::OnUpPress( Menu & model ) noexcept
{
	std::visit( [ & ]( auto const& menu )
	{
		using type = std::decay_t<decltype( menu )>;

		ButtonController::Deselect( type::buttons[ model.choice ] );

		--model.choice;
		if( model.choice < 0 )
			model.choice = type::numButtons - 1;

		ButtonController::Select( type::buttons[ model.choice ] );
		
	}, model.variant );
}

void sns::MenuController::OnDownPress( Menu & model ) noexcept
{
	std::visit( [ & ]( auto& menu )
	{
		using type = std::decay_t<decltype( menu )>;

		ButtonController::Deselect( type::buttons[ model.choice ] );

		++model.choice;
		model.choice %= type::numButtons;

		ButtonController::Select( type::buttons[ model.choice ] );

	}, model.variant );
}

void sns::MenuController::OnEnterPress( Menu & model, Game & game ) noexcept
{
	if( Choice( model ) == 0 )
	{
		GameController::TransitionState( game, Game::State::Play );
	}
	else if( Choice( model ) == 1 )
	{
		AppController::Kill();
	}
}
