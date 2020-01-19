#pragma once

#include "Game.h"
#include "Keyboard.h"
#include "Mouse.h"
#include "Settings.h"
#include "Surface.h"
#include "SurfaceController.h"
#include "Window.h"
#include <string>

class App
{
public:
	App( const wchar_t* pArgs );

private:
	friend class AppController;
	friend class AppView;
	friend class GameController;
	friend int WINAPI wWinMain( HINSTANCE hInst, HINSTANCE, LPWSTR pArgs, INT );

	mutable Surface render_target = SurfaceController::CreateSurface( int( sns::viewport_size.width ), int( sns::viewport_size.height ) );
	Window window;
	Keyboard kbd;
	Mouse mouse;
	Game game;
	std::wstring args;
};
