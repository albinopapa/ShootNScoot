#include "App.h"
#include "FontController.h"
#include "FontView.h"
#include "Game.h"
#include "GameController.h"
#include "GameView.h"
#include "Settings.h"
#include "Window.h"
#include "WindowView.h"
#include "MenuView.h"
#include "World.h"
#include "WorldController.h"
#include "WorldView.h"

void GameView::Draw( Game const& model, Surface& render_target )noexcept
{
	switch( model.state )
	{
		case Game::State::Intro:
		{
			FontView::Draw( 
				model.font, 
				"Press Enter/Return to start", 
				{ 176, 286 }, 
				Colors::White, 
				render_target
			);
			
			break;
		}
		case Game::State::Play:
		{
			sns::WorldView::Draw( model.world, render_target );

			const auto rtRect = SurfaceController::GetRect( render_target );

			const auto score_str = std::to_string( model.score );
			const auto glyph_width = float( FontController::GlyphWidth( model.font ) );
			const auto glyph_height = float( FontController::GlyphHeight( model.font ) );
			const auto pixel_length = float( score_str.size() ) * glyph_width;
			const auto x = rtRect.right - pixel_length;
			const auto y = glyph_height * .5f;

			FontView::Draw(
				model.font, 
				score_str, 
				{ x, y }, 
				Colors::White, 
				render_target
			);
			break;
		}
		case Game::State::MainMenu:
		case Game::State::PauseMenu:
		{
			sns::MenuView::Draw( model.menu, model.font, render_target );
			break;
		}
		case Game::State::Gameover:
		{
			if( sns::WorldController::CurrentLevelIndex( model.world ) > 2 )
			{
				FontView::Draw(
					model.font,
					"Congratulations, you've finished the demo.",
					{ 32, 246 },
					Colors::White,
					render_target
				);
			}
			else if( sns::WorldController::CurrentLevelIndex( model.world ) == 10 &&
				sns::WorldController::HeroWon( model.world ) )
			{
				FontView::Draw( 
					model.font, 
					"Congratulations, you've finished the game\nThe universe is safe for now.", 
					{ 32, 246 }, 
					Colors::White, 
					render_target
				);
			}

			FontView::Draw(
				model.font, 
				"Press Enter/Return to go back to the main menu", 
				{ 32, 272 }, 
				Colors::White, 
				render_target
			);

			break;
		}
	}
}
