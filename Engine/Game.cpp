#include "MainWindow.h"
#include "Game.h"

Game::Game( MainWindow& wnd )noexcept
	:
	wnd( wnd )
{}

void Game::Update( float dt )noexcept
{
	state = nextState;
	if( state == State::Play )
	{
		world.Update( dt );
	}
}

