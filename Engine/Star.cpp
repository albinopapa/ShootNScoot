#include "Star.h"

void sns::Star::Update() noexcept
{
	position += {0.f, speed };
}
