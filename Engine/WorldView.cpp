#include "WorldView.h"
#include "World.h"
#include "AmmoView.h"
#include "AsteroidView.h"
#include "Boss1View.h"
#include "EnemyView.h"
#include "HeroView.h"
#include "StarView.h"

namespace sns
{
	void WorldView::Draw( World const& model, Graphics & gfx )noexcept
	{
		for( auto const& star : model.stars ) StarView::Draw( star, gfx );

		HeroView::Draw( model.hero, gfx );

		for( auto const& bullet : model.hero_bullets ) AmmoView::Draw( bullet, gfx );
		for( auto const& bullet : model.enemy_bullets ) AmmoView::Draw( bullet, gfx );

		switch( model.state )
		{
			case WorldState::Arena:
			{
				for( auto const& enemy : model.enemies ) EnemyView::Draw( enemy, gfx );
				for( auto const& asteroid : model.asteroids ) AsteroidView::Draw( asteroid, gfx );
				break;
			}
			case WorldState::Boss:
			{
				Boss1View::Draw( model.boss, gfx );
				break;
			}
		}
	}
}
