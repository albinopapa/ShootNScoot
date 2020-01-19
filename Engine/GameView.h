#pragma once

class Game;
class Surface;
class GameView
{
public:
	static void Draw( Game const& model, Surface& render_target )noexcept;
};
