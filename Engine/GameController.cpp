#include "App.h"
#include "AppController.h"
#include "GameController.h"
#include "HeroController.h"
#include "KbdController.h"
#include "MenuController.h"
#include "WorldController.h"

void GameController::Update( Game& model )
{
#if defined(_DEBUG)
	const auto dt = .016f;
#else
	FrameTimer timer;
	const auto dt = TimerController::Mark( model.timer );
#endif

	model.state = model.nextState;
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
	return sns::MenuController::Choice( model.menu );
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
	KbdController::FlushKey( model.app.kbd );
}

void GameController::DoIntroState( Game& model )
{
	while( !KbdController::KeyIsEmpty( model.app.kbd ) )
	{
		if( const auto event = KbdController::ReadKey( model.app.kbd );
			event.IsPress() && ( event.GetCode() == VK_RETURN ) )
		{
			TransitionState( model, Game::State::MainMenu );
			model.menu = sns::MenuController::Create<sns::MainMenu>();
		}
	}
}

void GameController::DoMainMenuState( Game& model )
{
	while( !KbdController::KeyIsEmpty( model.app.kbd ) )
	{
		const auto event = KbdController::ReadKey( model.app.kbd );
		if( !event.IsPress() )continue;

		if( event.GetCode() == VK_DOWN )
		{
			sns::MenuController::OnDownPress( model.menu );
		}
		else if( event.GetCode() == VK_UP )
		{
			sns::MenuController::OnUpPress( model.menu );
		}
		else if( event.GetCode() == VK_RETURN )
		{
			sns::MenuController::OnEnterPress( model.menu, model );
		}
	}
}

void GameController::DoPlayState( Game& model, float dt )
{
	while( !KbdController::KeyIsEmpty( model.app.kbd ) )
	{
		if( const auto event = KbdController::ReadKey( model.app.kbd );
			event.IsPress() && ( event.GetCode() == VK_ESCAPE ) )
		{
			TransitionState( model, Game::State::PauseMenu );
			model.menu = sns::MenuController::Create<sns::PauseMenu>();
			return;
		}
	}

	sns::WorldController::Update( model.world, model.app.kbd, model, dt );

	if( sns::WorldController::HeroLost( model.world ) ||
		sns::WorldController::HeroWon( model.world ) )
	{
		TransitionState( model, Game::State::Gameover );
	}
}

void GameController::DoPauseMenuState( Game& model )
{
	while( !KbdController::KeyIsEmpty( model.app.kbd ) )
	{
		const auto event = KbdController::ReadKey( model.app.kbd );
		if( !event.IsPress() ) continue;

		if( event.GetCode() == VK_DOWN )
		{
			sns::MenuController::OnDownPress( model.menu );
		}
		else if( event.GetCode() == VK_UP )
		{
			sns::MenuController::OnUpPress( model.menu );
		}
		else if( event.GetCode() == VK_RETURN )
		{
			sns::MenuController::OnEnterPress( model.menu, model );
		}
		else if( event.GetCode() == VK_ESCAPE )
		{
			TransitionState( model, Game::State::Play );
		}
	}
}

void GameController::DoGameoverState( Game& model )
{
	while( !KbdController::KeyIsEmpty( model.app.kbd ) )
	{
		if( const auto event = KbdController::ReadKey( model.app.kbd );
			event.IsPress() && ( event.GetCode() == VK_RETURN ) )
		{
			TransitionState( model, Game::State::MainMenu );
			sns::WorldController::Reset( model.world );
			model.menu = sns::MenuController::Create<sns::MainMenu>();
		}
	}
}

