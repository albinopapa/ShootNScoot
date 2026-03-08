#pragma once

#include <math/dny_math.hpp>

class Camera{
public:
	Camera() = default;
	Camera( dny::vector2<float> position, dny::Rect<float> bounds )noexcept;

	void Update( float dt )noexcept;
	dny::Rect<float> GetBounds()const noexcept;
private:
	dny::vector2<float> position;
	dny::Rect<float> bounds;
};