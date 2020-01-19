#pragma once

#include "App.h"

class AppController
{
public:
	static void Update( App& model );
	static void Kill()noexcept;
	static bool ProcessMessage();

private:
	friend class Window;
	static LRESULT WINAPI _HandleMsgSetup( HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam );
	static LRESULT WINAPI _HandleMsgThunk( HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam );
	static LRESULT HandleMsg( App& model, HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam );

};