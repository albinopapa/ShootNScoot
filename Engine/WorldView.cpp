#include "WorldView.h"
#include "World.h"
#include "AmmoView.h"
#include "AsteroidView.h"
#include "Boss1View.h"
#include "EnemyView.h"
#include "HeroView.h"
#include "StarView.h"

void WorldView::Draw( World const& model, Graphics& gfx ) const noexcept
{
	StarView star_view;
	for( auto const& star : model.stars ) star_view.Draw( star, gfx );

	HeroView hero_view;
	hero_view.Draw( model.hero, gfx );

	AmmoView ammo_view;
	for( auto const& bullet : model.hero_bullets ) ammo_view.Draw( bullet, gfx );
	for( auto const& bullet : model.enemy_bullets ) ammo_view.Draw( bullet, gfx );

	switch( model.state )
	{
		case WorldState::Arena:
		{
			EnemyView enemy_view;
			for( auto const& enemy : model.enemies ) enemy_view.Draw( enemy, gfx );

			AsteroidView asteroid_view;
			for( auto const& asteroid : model.asteroids ) asteroid_view.Draw( asteroid, gfx );
			break;
		}
		case WorldState::Boss:
		{
			Boss1View boss_view;
			boss_view.Draw( model.boss, gfx );
			break;
		}
	}
}
