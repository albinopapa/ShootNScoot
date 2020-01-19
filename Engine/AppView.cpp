#include "App.h"
#include "AppView.h"
#include "GameView.h"
#include "SurfaceController.h"
#include "WindowView.h"

void AppView::Draw( App const & model )
{
	SurfaceController::Fill( model.render_target, Colors::Black );
	GameView::Draw( model.game, model.render_target );
	WindowView::Preset( model.window, model.render_target );
}
