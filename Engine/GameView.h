#pragma once

#include "ChiliWin.h"
#include "Enumerations.h"
#include "Font.h"
#include "Game.h"
#include "MainWindow.h"
#include "WorldView.h"

class GameView
{
public:
	GameView( MainWindow& wnd );
	void Draw( Game const& model )noexcept;

private:
	Font font = Font( "Images/Fixedsys16x28.bmp" );
	Graphics gfx;
};
