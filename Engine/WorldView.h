#pragma once
#include "World.h"
#include "Enumerations.h"
#include "Graphics.h"

	class WorldView
	{
	public:
		void Draw( World const& model, Graphics& gfx )const noexcept;
	};

