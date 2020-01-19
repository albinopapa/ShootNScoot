#pragma once

#include "Game.h"

class GameController
{
public:
	static void Update( Game& model_ );
	static void IncrementScore( Game& model, int amount )noexcept;
	
	static sns::World const& World( Game const& model )noexcept;
	static Game::State State( Game const& model )noexcept;
	static int MenuChoice( Game const& model )noexcept;
	static int Score( Game const& model )noexcept;

	static void TransitionState( Game& model, Game::State newState )noexcept;
private:

	static void DoIntroState( Game& model );
	static void DoMainMenuState( Game& model );
	static void DoPlayState( Game& model, float dt );
	static void DoPauseMenuState( Game& model );
	static void DoGameoverState( Game& model );
};