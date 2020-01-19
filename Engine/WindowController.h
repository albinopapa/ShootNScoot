#pragma once

#include "ChiliException.h"
#include "Rect.h"
#include "Window.h"
#include <string>
#undef IsMinimized

class WindowController
{
public:
	class Exception : public ChiliException
	{
	public:
		using ChiliException::ChiliException;
		virtual std::wstring GetFullMessage() const override { return GetNote() + L"\nAt: " + GetLocation(); }
		virtual std::wstring GetExceptionType() const override { return L"Windows Exception"; }
	};

public:
	static bool IsActive( Window const& model )noexcept;
	static bool IsMinimized( Window const& model )noexcept;
	static void ShowMessageBox(
		Window const& model,
		const std::wstring& title,
		const std::wstring& message,
		uint32_t type = MB_OK )noexcept;
};