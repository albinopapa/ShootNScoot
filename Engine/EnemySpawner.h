#pragma once

namespace sns
{
	class Enemy;
	class EnemySpawner
	{
	public:
		static Enemy Spawn( int enemy_spawn_group )noexcept;
	};
}