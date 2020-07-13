#include "GameController.h"
#include "MainWindow.h"

void GameController::Update( Game& model, float dt )
{
	switch( model.state )
	{
		case GameState::Intro:
			DoIntroState( model );
			break;
		case GameState::MainMenu:
			DoMainMenuState( model );
			break;
		case GameState::Play:
			DoPlayState( model, dt );
			break;
		case GameState::PauseMenu:
			DoPauseMenuState( model );
			break;
		case GameState::Gameover:
			DoGameoverState( model );
			break;
	}
}

void GameController::DoIntroState( Game& model )
{
	while( !model.wnd.kbd.KeyIsEmpty() )
	{
		if( const auto event = model.wnd.kbd.ReadKey();
			event.IsPress() && ( event.GetCode() == VK_RETURN ) )
		{
			model.TransitionState( GameState::MainMenu );
		}
	}
}

void GameController::DoMainMenuState( Game& model )
{
	int menu_choice = model.menu_choice;

	while( !model.wnd.kbd.KeyIsEmpty() )
	{
		if( const auto event = model.wnd.kbd.ReadKey(); event.IsPress() )
		{
			if( event.GetCode() == VK_DOWN )
			{
				menu_choice = ( menu_choice + 1 ) % 2;
			}
			else if( event.GetCode() == VK_UP )
			{
				--menu_choice;
				if( menu_choice < 0 )
				{
					menu_choice += 2;
				}
			}
			else if( event.GetCode() == VK_RETURN )
			{
				if( menu_choice == 0 )
				{
					model.TransitionState( GameState::Play );
				}
				else
				{
					model.wnd.Kill();
				}
			}
		}
	}

	model.menu_choice = menu_choice;
}

void GameController::DoPlayState( Game& model, float dt )
{
	while( !model.wnd.kbd.KeyIsEmpty() )
	{
		if( const auto event = model.wnd.kbd.ReadKey();
			event.IsPress() && ( event.GetCode() == VK_ESCAPE ) )
		{
			model.TransitionState( GameState::PauseMenu );
			return;
		}
	}

	world.Update( model.world, model.wnd.kbd, model, dt );

	if( model.world.hero.health <= 0.f ||
		model.world.state == WorldState::LevelComplete )
	{
		model.TransitionState( GameState::Gameover );
	}
}

void GameController::DoPauseMenuState( Game& model )
{
	auto menu_choice = model.menu_choice;
	while( !model.wnd.kbd.KeyIsEmpty() )
	{
		if( const auto event = model.wnd.kbd.ReadKey(); event.IsPress() )
		{
			if( event.GetCode() == VK_DOWN )
			{
				menu_choice = ( menu_choice + 1 ) % 2;
			}
			else if( event.GetCode() == VK_UP )
			{
				--menu_choice;
				if( menu_choice < 0 ) menu_choice += 2;
			}
			else if( event.GetCode() == VK_RETURN )
			{
				if( menu_choice == 0 )
				{
					model.TransitionState( GameState::Play );
				}
				else
				{
					model.wnd.Kill();
				}
			}
			else if( event.GetCode() == VK_ESCAPE )
			{
				model.TransitionState( GameState::Play );
			}
		}
	}

	model.menu_choice = menu_choice;
}

void GameController::DoGameoverState( Game& model )
{
	while( !model.wnd.kbd.KeyIsEmpty() )
	{
		if( const auto event = model.wnd.kbd.ReadKey();
			event.IsPress() && ( event.GetCode() == VK_RETURN ) )
		{
			model.TransitionState( GameState::MainMenu );
			world.Reset( model.world );
		}
	}
}
