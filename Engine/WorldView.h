#pragma once

class Surface;
namespace sns
{
	class World;

	class WorldView
	{
	public:
		static void Draw( World const& model, Surface& render_target )noexcept;
	};
}
