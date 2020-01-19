#pragma once

#include "Colors.h"
#include "Rect.h"
#include <string>

class Surface;
class SurfaceController
{
public:
	static Surface CreateSurface( const std::string& filename );
	static Surface CreateSurface( int width, int height );

	static void PutPixel( Surface& model, Point const& position, Color c )noexcept;
	static Color GetPixel( Surface const& model, Point const& position )noexcept;
	static int GetWidth( Surface const& model )noexcept;
	static int GetHeight( Surface const& model )noexcept;
	static RectF GetRect( Surface const& model )noexcept;
	static void Fill( Surface& model, Color c )noexcept;
	static const Color* Data( Surface const& model )noexcept;
};