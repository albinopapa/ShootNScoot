#include "GameView.h"
#include "Game.h"
#include "WorldView.h"

GameView::GameView( MainWindow& wnd )
	:
	gfx( wnd )
{}

void GameView::Draw( Game const& model )noexcept
{
	gfx.BeginFrame();

	switch( model.state )
	{
		case GameState::Intro:
		{
			font.DrawText( "Press Enter/Return to start", { 176, 286 }, Colors::White, gfx );
			break;
		}
		case GameState::MainMenu:
		{
			font.DrawText( "Start game", { 200, 272 }, model.menu_choice == 0 ? Colors::Magenta : Colors::White, gfx );
			font.DrawText( "Quit game", { 200, 328 }, model.menu_choice == 1 ? Colors::Magenta : Colors::White, gfx );
			break;
		}
		case GameState::Play:
		{
			auto world_view = sns::WorldView{};
			world_view.Draw( model.world, gfx );

			const auto score_str = std::to_string( model.score );
			const auto pixel_length = ( int( score_str.size() ) * font.GlyphWidth() );
			const auto x = Graphics::ScreenWidth - pixel_length;
			const auto y = font.GlyphHeight() / 2;
			font.DrawText( score_str, { x, y }, Colors::White, gfx );

			break;
		}
		case GameState::PauseMenu:
		{
			font.DrawText( "Resume game", { 200, 272 }, model.menu_choice == 0 ? Colors::Magenta : Colors::White, gfx );
			font.DrawText( "Quit game", { 200, 328 }, model.menu_choice == 1 ? Colors::Magenta : Colors::White, gfx );
			break;
		}
		case GameState::Gameover:
		{
			if( model.world.state == WorldState::LevelComplete )
				font.DrawText( "Congratulations, you've finished the demo.", { 32, 246 }, Colors::White, gfx );

			font.DrawText( "Press Enter/Return to go back to the main menu", { 32, 272 }, Colors::White, gfx );

			break;
		}
	}

	gfx.EndFrame();
}
