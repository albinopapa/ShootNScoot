#pragma once

#include "Colors.h"
#include "Rect.h"
#include <string>
#include <memory>

class Surface
{
public:
	Surface() = default;
	Surface( Surface&& donor );
	Surface( const std::string& filename );
	Surface( int width,int height );

	Surface& operator=( Surface&& rhs );

	void PutPixel( int x,int y,Color c );
	Color GetPixel( int x,int y ) const;
	int GetWidth() const;
	int GetHeight() const;
	RectI GetRect() const;
	void Fill( Color c );
	const Color* Data() const;
	Color* Data();
private:
	std::unique_ptr<Color[]> pixels;
	int width = 0;
	int height = 0;
};