#pragma once

#include "Font.h"
#include "FrameTimer.h"
#include "Keyboard.h"
#include "Menus.h"
#include "Mouse.h"
#include "Surface.h"
#include "World.h"

class Game
{
public:
	enum class State { Intro, MainMenu, Play, PauseMenu, Gameover }; 

public:
	Game( class App& app_ )noexcept;
	Game( const Game& ) = delete;
	Game& operator=( const Game& ) = delete;

private:
	friend class GameController;
	friend class GameView;

	sns::World world;
	sns::Menu menu = sns::Menu{ sns::MainMenu{} };
	Font font = Font( "Images/Fixedsys16x28.bmp" );
	FrameTimer timer;
	App& app;
	State state			= State::Intro;
	State nextState		= State::Intro;
	int score = 0;
};
