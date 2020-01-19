#include "MouseController.h"


Vei2 const& MouseController::GetPos( Mouse const& model )noexcept
{
	return model.position;
}

int MouseController::GetPosX( Mouse const& model )noexcept
{
	return model.position.x;
}

int MouseController::GetPosY( Mouse const& model )noexcept
{
	return model.position.y;
}

bool MouseController::LeftIsPressed( Mouse const& model )noexcept
{
	return model.leftIsPressed;
}

bool MouseController::RightIsPressed( Mouse const& model )noexcept
{
	return model.rightIsPressed;
}

bool MouseController::IsInWindow( Mouse const& model )noexcept
{
	return model.isInWindow;
}

Mouse::Event MouseController::Read( Mouse& model )noexcept
{
	if( model.buffer.size() > 0u )
	{
		Mouse::Event e = model.buffer.front();
		model.buffer.pop();
		return e;
	}
	else
	{
		return Mouse::Event();
	}
}

bool MouseController::IsEmpty( Mouse const & model ) noexcept
{
	return model.buffer.empty();
}

void MouseController::Flush( Mouse& model )noexcept
{
	model.buffer = std::queue<Mouse::Event>();
}

void MouseController::OnMouseLeave( Mouse& model )noexcept
{
	model.isInWindow = false;
}

void MouseController::OnMouseEnter( Mouse& model )noexcept
{
	model.isInWindow = true;
}

void MouseController::OnMouseMove( Mouse& model, int newx, int newy )
{
	model.position = { newx, newy };

	model.buffer.push( Mouse::Event( Mouse::Event::Type::Move, model ) );
	TrimBuffer( model );
}

void MouseController::OnLeftPressed( Mouse& model, int x, int y )
{
	model.leftIsPressed = true;

	model.buffer.push( Mouse::Event( Mouse::Event::Type::LPress, model ) );
	TrimBuffer( model );
}

void MouseController::OnLeftReleased( Mouse& model, int x, int y )
{
	model.leftIsPressed = false;

	model.buffer.push( Mouse::Event( Mouse::Event::Type::LRelease, model ) );
	TrimBuffer( model );
}

void MouseController::OnRightPressed( Mouse& model, int x, int y )
{
	model.rightIsPressed = true;

	model.buffer.push( Mouse::Event( Mouse::Event::Type::RPress, model ) );
	TrimBuffer( model );
}

void MouseController::OnRightReleased( Mouse& model, int x, int y )
{
	model.rightIsPressed = false;

	model.buffer.push( Mouse::Event( Mouse::Event::Type::RRelease, model ) );
	TrimBuffer( model );
}

void MouseController::OnWheelUp( Mouse& model, int x, int y )
{
	model.buffer.push( Mouse::Event( Mouse::Event::Type::WheelUp, model ) );
	TrimBuffer( model );
}

void MouseController::OnWheelDown( Mouse& model, int x, int y )
{
	model.buffer.push( Mouse::Event( Mouse::Event::Type::WheelDown, model ) );
	TrimBuffer( model );
}

void MouseController::TrimBuffer( Mouse& model )noexcept
{
	while( model.buffer.size() > Mouse::bufferSize )
	{
		model.buffer.pop();
	}
}