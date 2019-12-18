/****************************************************************************************** 
 *	Chili DirectX Framework Version 16.07.20											  *	
 *	Game.cpp																			  *
 *	Copyright 2016 PlanetChili.net <http://www.planetchili.net>							  *
 *																						  *
 *	This file is part of The Chili DirectX Framework.									  *
 *																						  *
 *	The Chili DirectX Framework is free software: you can redistribute it and/or modify	  *
 *	it under the terms of the GNU General Public License as published by				  *
 *	the Free Software Foundation, either version 3 of the License, or					  *
 *	(at your option) any later version.													  *
 *																						  *
 *	The Chili DirectX Framework is distributed in the hope that it will be useful,		  *
 *	but WITHOUT ANY WARRANTY; without even the implied warranty of						  *
 *	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the						  *
 *	GNU General Public License for more details.										  *
 *																						  *
 *	You should have received a copy of the GNU General Public License					  *
 *	along with The Chili DirectX Framework.  If not, see <http://www.gnu.org/licenses/>.  *
 ******************************************************************************************/
#include "MainWindow.h"
#include "Game.h"
#include "SpriteEffect.h"


Game::Game( MainWindow& wnd )
	:
	wnd( wnd ),
	gfx( wnd )
{
	world.hero.position = screenRect.Center();
	world.hero.velocity = { 0.f, 0.f };
}

void Game::Go()
{
	UpdateModel();
	gfx.BeginFrame();
	ComposeFrame();
	gfx.EndFrame();
}

void Game::UpdateModel()
{
#if defined(_DEBUG)
	const auto dt = .016f;
#else
	const auto dt = timer.Mark();
#endif

	state = nextState;

	switch( state )
	{
		case State::Intro:
			DoIntroState();
			break;
		case State::MainMenu:
			DoMainMenuState();
			break;
		case State::Play:
			DoPlayState( dt );
			break;
		case State::PauseMenu:
			DoPauseMenuState();
			break;
		case State::Gameover:
			DoGameoverState();
			break;
	}
}

void Game::DoIntroState()
{
	while( !wnd.kbd.KeyIsEmpty() )
	{
		if( const auto event = wnd.kbd.ReadKey(); 
			event.IsPress() && ( event.GetCode() == VK_RETURN ) )
		{
			TransitionState( State::MainMenu );
		}
	}
}

void Game::DoMainMenuState()
{
	while( !wnd.kbd.KeyIsEmpty() )
	{
		if( const auto event = wnd.kbd.ReadKey(); event.IsPress() )
		{
			if( event.GetCode() == VK_DOWN )
			{
				menu_choice = ( menu_choice + 1 ) % 2;
			}
			else if(event.GetCode() == VK_UP)
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
					TransitionState( State::Play );
				}
				else
				{
					wnd.Kill();
				}
			}
		}
	}
}

void Game::DoPlayState( float dt )
{
	while( !wnd.kbd.KeyIsEmpty() )
	{
		if( const auto event = wnd.kbd.ReadKey();
			event.IsPress() && ( event.GetCode() == VK_ESCAPE ) )
		{
			TransitionState( State::PauseMenu );
			return;
		}
	}

	world.Update( wnd.kbd, dt );
	if( world.hero.health <= 0.f || world.state == sns::World::State::LevelComplete )
		TransitionState( State::Gameover );

}

void Game::DoPauseMenuState()
{
	while( !wnd.kbd.KeyIsEmpty() )
	{
		if( const auto event = wnd.kbd.ReadKey(); event.IsPress() )
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
					TransitionState( State::Play );
				else
					wnd.Kill();
			}
			else if( event.GetCode() == VK_ESCAPE )
			{
				TransitionState( State::Play );
			}
		}
	}
}

void Game::DoGameoverState()
{
	while( !wnd.kbd.KeyIsEmpty() )
	{
		if( const auto event = wnd.kbd.ReadKey(); 
			event.IsPress() && ( event.GetCode() == VK_RETURN ) )
		{
			TransitionState( State::MainMenu );
			world.Reset();
		}
	}
}

void Game::TransitionState( State newState )
{
	nextState = newState;
	wnd.kbd.FlushKey();
	menu_choice = 0;
}

void Game::ComposeFrame()
{
	switch( state )
	{
		case State::Intro:
			font.DrawText( "Press Enter/Return to start", { 176, 286 }, Colors::White, gfx );
			break;
		case State::MainMenu:
			font.DrawText( "Start game", { 200, 272 }, menu_choice == 0 ? Colors::Magenta : Colors::White, gfx );
			font.DrawText( "Quit game", { 200, 328 }, menu_choice == 1 ? Colors::Magenta : Colors::White, gfx );
			break;
		case State::Play:
		{
			world.Draw( gfx );

			const auto score_str = std::to_string( world.score );
			const auto pixel_length = ( int( score_str.size() ) * 16 );
			const auto x = Graphics::ScreenWidth - pixel_length;
			const auto y = 4;
			font.DrawText( score_str, { x, y }, Colors::White, gfx );

			break;
		}
		case State::PauseMenu:
			font.DrawText( "Resume game", { 200, 272 }, menu_choice == 0 ? Colors::Magenta : Colors::White, gfx );
			font.DrawText( "Quit game", { 200, 328 }, menu_choice == 1 ? Colors::Magenta : Colors::White, gfx );
			break;
		case State::Gameover:
			if( world.state == sns::World::State::LevelComplete )
				font.DrawText( "Congratulations, you've finished the demo.", { 32, 246 }, Colors::White, gfx );

			font.DrawText( "Press Enter/Return to go back to the main menu", { 32, 272 }, Colors::White, gfx );

			break;
	}
}
