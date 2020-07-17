#pragma once

#include "Enumerations.h"
#include "Font.h"
#include "ChiliWin.h"
#include "MainWindow.h"
#include "WorldView.h"
#include "Game.h"
class GameView
{
public:
	GameView( MainWindow& wnd );
	void Draw( Game const& model )noexcept;

private:
	Font font = Font( "Images/Fixedsys16x28.bmp" );
	Graphics gfx;
};
