#include "Camera.h"

Camera::Camera( dny::vector2<float> position, dny::Rect<float> bounds ) noexcept
	:
	position( position ),
	bounds( bounds ){}

dny::Rect<float> Camera::GetBounds() const noexcept{
	return bounds + position;
}
