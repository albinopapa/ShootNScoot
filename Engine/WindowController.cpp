#include "Window.h"
#include "WindowController.h"
#include "RectController.h"


bool WindowController::IsActive( Window const& model )noexcept
{
	return GetActiveWindow() == model.hWnd;
}

bool WindowController::IsMinimized( Window const& model )noexcept
{
	return ::IsIconic( model.hWnd ) != 0;
}

void WindowController::ShowMessageBox(
	Window const& model,
	const std::wstring& title,
	const std::wstring& message,
	uint32_t type )noexcept
{
	MessageBox( model.hWnd, message.c_str(), title.c_str(), type );
}
