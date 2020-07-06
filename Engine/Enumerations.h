#pragma once

enum class AsteroidDeathReason
{
	None, LeftScreen, AffectedByPlayer, AffectedByEnemy, AffectedByAsteroid
};

enum class Boss1State { Idle, Attack, Regen };

enum class AmmoOwner { Hero, Enemy };

enum class GameState { Intro, MainMenu, Play, PauseMenu, Gameover };

enum class ShieldState { Full, Recharging, Depleted };

enum class WeaponState { Idle, Recharge };

// Arena state is actual level play: spawns enemies and asteroids
// Boss state spawns boss and runs boss update: disables asteroid and automatic enemy spawns
enum class WorldState { Arena, Boss, LevelComplete };