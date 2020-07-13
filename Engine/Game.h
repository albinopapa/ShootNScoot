/****************************************************************************************** 
 *	Chili DirectX Framework Version 16.07.20											  *	
 *	Game.h																				  *
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
#pragma once

#include "Enumerations.h"
#include "World.h"

class Game
{
public:
	Game( class MainWindow& wnd )noexcept;
	Game( const Game& ) = delete;
	Game& operator=( const Game& ) = delete;
	void Update( float dt )noexcept;

	void IncrementScore( int amount )noexcept;
private:

	/********************************/
	/*  User Functions              */
	/********************************/
	void TransitionState( GameState newState )noexcept;
private:
	friend class GameView;
	friend class GameController;

	MainWindow& wnd;
	/********************************/
	/*  User Variables              */
	/********************************/
	sns::World world;
	GameState state			= GameState::Intro;
	GameState nextState		= GameState::Intro;

	int menu_choice = 0;
	int score = 0;
};
