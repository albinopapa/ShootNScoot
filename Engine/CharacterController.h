#pragma once

#include "Vec2.h"

class Character;

class CharacterController
{
public:
	static void SetDirection( Character& model, const Vec2& dir )noexcept;
	static void Update( Character& model, float dt )noexcept;
	// activates a damage visual effect
	static void ActivateEffect( Character& model )noexcept;

};