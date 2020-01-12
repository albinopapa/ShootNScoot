#include "GameController.h"
#include "Game.h"
#include "HeroController.h"
#include "MainWindow.h"
#include "WorldController.h"

void GameController::Update( Game& model, float dt )
{
	switch( model.state )
	{
		case Game::State::Intro:
			DoIntroState( model );
			break;
		case Game::State::MainMenu:
			DoMainMenuState( model );
			break;
		case Game::State::Play:
			DoPlayState( model, dt );
			break;
		case Game::State::PauseMenu:
			DoPauseMenuState( model );
			break;
		case Game::State::Gameover:
			DoGameoverState( model );
			break;
	}
}

void GameController::IncrementScore( Game & model, int amount ) noexcept
{
	model.score += amount;
}

Game::State GameController::State( Game const & model ) noexcept
{
	return model.state;
}

int GameController::MenuChoice( Game const & model ) noexcept
{
	return model.menu_choice;
}

sns::World const & GameController::World( Game const & model ) noexcept
{
	return model.world;
}

int GameController::Score( Game const & model ) noexcept
{
	return model.score;
}

void GameController::TransitionState( Game& model, Game::State newState )noexcept
{
	model.nextState = newState;
	model.wnd.kbd.FlushKey();
	model.menu_choice = 0;
}

void GameController::DoIntroState( Game& model )
{
	while( !model.wnd.kbd.KeyIsEmpty() )
	{
		if( const auto event = model.wnd.kbd.ReadKey();
			event.IsPress() && ( event.GetCode() == VK_RETURN ) )
		{
			TransitionState( model, Game::State::MainMenu );
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
					TransitionState( model, Game::State::Play );
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
			TransitionState( model, Game::State::PauseMenu );
			return;
		}
	}

	sns::World::Controller::Update( model.world, model.wnd.kbd, model, dt );

	if( sns::World::Controller::HeroLost( model.world ) ||
		sns::World::Controller::HeroWon( model.world ) )
	{
		TransitionState( model, Game::State::Gameover );
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
					TransitionState( model, Game::State::Play );
				}
				else
				{
					model.wnd.Kill();
				}
			}
			else if( event.GetCode() == VK_ESCAPE )
			{
				TransitionState( model, Game::State::Play );
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
			TransitionState( model, Game::State::MainMenu );
			sns::WorldController::Reset( model.world );
		}
	}
}

