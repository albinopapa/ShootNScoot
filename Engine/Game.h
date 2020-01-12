#pragma once

#include "World.h"

struct Game
{
public:
	using Controller = struct GameController;
	enum class State { Intro, MainMenu, Play, PauseMenu, Gameover }; 

public:
	Game( class MainWindow& wnd )noexcept;
	Game( const Game& ) = delete;
	Game& operator=( const Game& ) = delete;
	void Update( float dt )noexcept;

private:
	friend struct GameController;
	MainWindow& wnd;
	sns::World world;
	State state			= State::Intro;
	State nextState		= State::Intro;
	int menu_choice = 0;
	int score = 0;
};
