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

enum class WorldState { Arena, Boss, LevelComplete };