#pragma once

#include "Keyboard.h"

class KbdController
{
public:
	static void FlushKey( Keyboard& model )noexcept;
	static void FlushChar( Keyboard& model )noexcept;
	static void Flush( Keyboard& model )noexcept;
	static void EnableAutorepeat( Keyboard& model )noexcept;
	static void DisableAutorepeat( Keyboard& model )noexcept;
	static bool KeyIsPressed( Keyboard const& model, unsigned char keycode )noexcept;
	static Keyboard::Event ReadKey( Keyboard& model )noexcept;
	static bool KeyIsEmpty( Keyboard const& model )noexcept;
	static char ReadChar( Keyboard& model )noexcept;
	static bool CharIsEmpty( Keyboard const& model )noexcept;
	static bool AutorepeatIsEnabled( Keyboard const& model )noexcept;

private:
	friend class AppController;
	static void OnKeyPressed( Keyboard& model, unsigned char keycode );
	static void OnKeyReleased( Keyboard& model, unsigned char keycode );
	static void OnChar( Keyboard& model, char character );
	static void ClearState( Keyboard& model )noexcept;
	template<typename T>
	static void TrimBuffer( Keyboard& model, std::queue<T>& buffer )noexcept;

};