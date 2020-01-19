#include "WorldView.h"
#include "World.h"
#include "AmmoView.h"
#include "AsteroidView.h"
#include "BossView.h"
#include "EnemyView.h"
#include "HeroView.h"
#include "StarView.h"

namespace sns
{
	void WorldView::Draw( World const& model, Surface& render_target )noexcept
	{
		for( auto const& star : model.stars ) StarView::Draw( star, render_target );

		HeroView::Draw( model.hero, render_target );

		for( auto const& bullet : model.hero_bullets ) AmmoView::Draw( bullet, render_target );
		for( auto const& bullet : model.enemy_bullets ) AmmoView::Draw( bullet, render_target );

		switch( model.state )
		{
			case World::State::Arena:
			{
				for( auto const& enemy : model.enemies ) EnemyView::Draw( enemy, render_target );
				for( auto const& asteroid : model.asteroids ) AsteroidView::Draw( asteroid, render_target );
				break;
			}
			case World::State::Boss:
			{
				BossView::Draw( model.boss, render_target );
				break;
			}
		}
	}
}
