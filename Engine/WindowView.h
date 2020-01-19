#pragma once

class Surface;
class Window;

class WindowView
{
public:
	static void Preset( Window const& model, Surface const& pixel_buffer );
};