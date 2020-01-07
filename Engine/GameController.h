#pragma once

class Game;

class GameController
{
public:
	static void Update( Game& model_, float dt );
	static void IncrementScore( Game& model, int amount )noexcept;

private:
	static void DoIntroState( Game& model );
	static void DoMainMenuState( Game& model );
	static void DoPlayState( Game& model, float dt );
	static void DoPauseMenuState( Game& model );
	static void DoGameoverState( Game& model );
};