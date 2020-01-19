/****************************************************************************************** 
 *	Chili DirectX Framework Version 16.07.20											  *	
 *	Mouse.h																				  *
 *	Copyright 2016 PlanetChili <http://www.planetchili.net>								  *
 *																						  *
 *	This file is part of The Chili DirectX Framework.									  *
 *																						  *
 *	The Chili DirectX Framework is free software: you can redistribute it and/or modify	  *
 *	it under the terms of the GNU General Public License as published by				  *
 *	the Free Software Foundation, either version 3 of the License, or					  *
 *	(at your option) any later version.													  *
 *																						  *
 *	The Chili DirectX Framework is distributed in the hope that it will be useful,		  *
 *	but WITHOUT ANY WARRANTY; without even the implied warranty of						  *
 *	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the						  *
 *	GNU General Public License for more details.										  *
 *																						  *
 *	You should have received a copy of the GNU General Public License					  *
 *	along with The Chili DirectX Framework.  If not, see <http://www.gnu.org/licenses/>.  *
 ******************************************************************************************/
#pragma once

#include "Vec2.h"
#include <queue>

class Mouse
{
public:
	Mouse() = default;

public:
	class Event
	{
	public:
		enum class Type
		{
			LPress,
			LRelease,
			RPress,
			RRelease,
			WheelUp,
			WheelDown,
			Move,
			Invalid
		};
	public:
		Event() = default;
		Event( Type type, const Mouse& parent )
			:
			type( type ),
			leftIsPressed( parent.leftIsPressed ),
			rightIsPressed( parent.rightIsPressed ),
			position( parent.position )
		{}
		bool IsValid()const noexcept
		{
			return type != Type::Invalid;
		}
		Type GetType()const noexcept
		{
			return type;
		}
		Vei2 const& GetPos()const noexcept
		{
			return position;
		}
		int GetPosX()const noexcept
		{
			return position.x;
		}
		int GetPosY()const noexcept
		{
			return position.y;
		}
		bool LeftIsPressed()const noexcept
		{
			return leftIsPressed;
		}
		bool RightIsPressed()const noexcept
		{
			return rightIsPressed;
		}

	private:
		Point position = { 0, 0 };
		Type type = Type::Invalid;
		bool leftIsPressed = false;
		bool rightIsPressed = false;
	};

private:
	Mouse( const Mouse& ) = delete;
	Mouse& operator=( const Mouse& ) = delete;

private:
	friend class MouseController;
	static constexpr unsigned int bufferSize = 4u;
	std::queue<Event> buffer;
	Point position;
	bool leftIsPressed = false;
	bool rightIsPressed = false;
	bool isInWindow = false;
};
