#pragma once

#include "Mouse.h"

class MouseController
{
public:
	static Vei2 const& GetPos( Mouse const& model )noexcept;
	static int GetPosX( Mouse const& model )noexcept;
	static int GetPosY( Mouse const& model )noexcept;
	static bool LeftIsPressed( Mouse const& model )noexcept;
	static bool RightIsPressed( Mouse const& model )noexcept;
	static bool IsInWindow( Mouse const& model )noexcept;
	static Mouse::Event Read( Mouse& model )noexcept;
	static bool IsEmpty( Mouse const& model )noexcept;
	static void Flush( Mouse& model )noexcept;
private:
	friend class AppController;
	static void OnMouseMove( Mouse& model, int x, int y );
	static void OnMouseLeave( Mouse& model )noexcept;
	static void OnMouseEnter( Mouse& model )noexcept;
	static void OnLeftPressed( Mouse& model, int x, int y );
	static void OnLeftReleased( Mouse& model, int x, int y );
	static void OnRightPressed( Mouse& model, int x, int y );
	static void OnRightReleased( Mouse& model, int x, int y );
	static void OnWheelUp( Mouse& model, int x, int y );
	static void OnWheelDown( Mouse& model, int x, int y );
	static void TrimBuffer( Mouse& model )noexcept;
};