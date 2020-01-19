#pragma once

#include "Button.h"
#include <array>
#include <string>
#include <variant>


namespace sns
{
	struct MainMenu
	{
		static constexpr int numButtons = 2;
		inline static std::array<Button, numButtons> buttons = {
			Button{ "Start Game", { 200, 272 }, Button::selected_color   },
			Button{ "Quit Game",  { 200, 328 }, Button::deselected_color }
		};
	};

	struct PauseMenu
	{
		static constexpr int numButtons = 2;
		inline static std::array<Button, numButtons> buttons = {
			Button{ "Resume game", { 200, 272 }, Button::selected_color   },
			Button{ "Quit game",   { 200, 328 }, Button::deselected_color }
		};
	};

	class Menu
	{
	public:
		using MenuType = std::variant<MainMenu, PauseMenu>;

	public:
		Menu( MenuType type )noexcept :variant( type ) {}

	private:
		friend class MenuController;
		friend class MenuView;

		MenuType variant;
		int choice = 0;
	};
}