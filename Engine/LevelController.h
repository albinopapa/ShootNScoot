#pragma once

namespace sns
{
	class Boss;
	class Level;
	class World;
	class LevelController
	{
	public:
		static void Update( Level& model, World& world, float dt )noexcept;
		static void Advance( Level& model )noexcept;
		static Boss SpawnBoss( Level const& model )noexcept;
		static int CurrentLevelIndex( Level const& model )noexcept;
		static bool AsteroidSpawnerComplete( Level const& model )noexcept;
		static bool EnemySpawnerComplete( Level const& model )noexcept;
		static bool IsFinal( Level const& model )noexcept;
		static void Reset( Level& model )noexcept;

	private:
		static void UpdateAsteroidSpawner( Level& model, World& world, float dt )noexcept;
		static void UpdateEnemySpawner( Level& model, World& world, float dt )noexcept;
	};
}