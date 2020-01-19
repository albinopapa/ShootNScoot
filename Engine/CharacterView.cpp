#include "CharacterView.h"
#include "Character.h"
#include "AnimationView.h"

void CharacterView::Draw( Character const & model, Surface& render_target ) const
{
	const auto& animation = model.animations[ ( int )model.iCurSequence ];

	// if effect active, draw sprite replacing opaque pixels with red
	if( model.effectActive )
	{
		AnimationView::Draw( animation, model.pos, render_target, Colors::Red );
	}
	else
	{
		AnimationView::Draw( animation, model.pos, render_target );
	}
}
