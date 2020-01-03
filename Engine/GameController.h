#pragma once

#include "WorldController.h"

class Game;

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
	sns::WorldController world;
};