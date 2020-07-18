#include "GameView.h"

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
			const auto msg = std::string{ "Press Enter/Return to start" };
			const auto x = ( Graphics::ScreenWidth - ( int( msg.length() ) * font.GlyphWidth() ) ) / 2;
			const auto y = ( Graphics::ScreenHeight - font.GlyphHeight() ) / 2;
			font.DrawText( msg, { x, y }, Colors::White, gfx );
			break;
		}
		case GameState::MainMenu:
		{
			const auto x = ( Graphics::ScreenWidth - ( 10 * font.GlyphWidth() ) ) / 2;
			auto y = ( Graphics::ScreenHeight - ( 2 * font.GlyphHeight() ) ) / 2;
			if( model.menu_choice == 0 ) {
				font.DrawText( "Start game", { x, y }, Colors::Magenta, gfx );
				font.DrawText( "Quit game", { x, y + font.GlyphHeight() }, Colors::White, gfx );
			}
			else if( model.menu_choice == 1 ) {
				font.DrawText( "Start game", { x, y }, Colors::White, gfx );
				font.DrawText( "Quit game", { x, y + font.GlyphHeight() }, Colors::Magenta, gfx );
			}
			break;
		}
		case GameState::Play:
		{
			auto world_view = WorldView{};
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
			const auto x = ( Graphics::ScreenWidth - ( 11 * font.GlyphWidth() ) ) / 2;
			auto y = ( Graphics::ScreenHeight - ( 2 * font.GlyphHeight() ) ) / 2;
			if( model.menu_choice == 0 ) {
				font.DrawText( "Start game", { x, y }, Colors::Magenta, gfx );
				font.DrawText( "Quit game", { x, y + font.GlyphHeight() }, Colors::White, gfx );
			}
			else if( model.menu_choice == 1 ) {
				font.DrawText( "Start game", { x, y }, Colors::White, gfx );
				font.DrawText( "Quit game", { x, y + font.GlyphHeight() }, Colors::Magenta, gfx );
			}
			break;
		}
		case GameState::Gameover:
		{
			const auto demo_finish = std::string{ "Congratulations, you've finished the demo." };
			const auto return_msg = std::string{ "Press Enter/Return to go back to the main menu" };
			const auto x = ( Graphics::ScreenWidth - ( 46 * font.GlyphWidth() ) ) / 2;
			const auto y = ( Graphics::ScreenHeight - ( 2 * font.GlyphHeight() ) ) / 2;
			if( model.world.state == WorldState::LevelComplete )
				font.DrawText( demo_finish, { x, y }, Colors::White, gfx );

			font.DrawText( return_msg, { x, y + font.GlyphHeight() }, Colors::White, gfx );

			break;
		}
	}

	gfx.EndFrame();
}
