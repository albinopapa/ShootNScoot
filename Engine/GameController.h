#pragma once

#include "Game.h"
#include "WorldController.h"

class GameController
{
public:
	void Update( Game& model_, float dt );

private:
	void DoIntroState( Game& model );
	void DoMainMenuState( Game& model );
	void DoPlayState( Game& model, float dt );
	void DoPauseMenuState( Game& model );
	void DoGameoverState( Game& model );

private:
	WorldController world;
};