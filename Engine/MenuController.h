#pragma once

#include "Menus.h"

class Game;
class GameController;

namespace sns
{
	class MenuController
	{
	public:
		template<typename MenuType>
		static Menu Create()noexcept { return { MenuType{} }; }
		static int Choice( Menu const& model )noexcept;
	private:
		friend class GameController;
		static void OnUpPress( Menu& model )noexcept;
		static void OnDownPress( Menu& model )noexcept;
		static void OnEnterPress( Menu& model, Game& game )noexcept;
	};
}