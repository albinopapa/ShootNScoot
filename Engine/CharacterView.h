#pragma once

class Character;
class Surface;

class CharacterView
{
public:
	void Draw( Character const& model, Surface& render_target ) const;
};

