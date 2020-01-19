#include "KbdController.h"

void KbdController::FlushKey( Keyboard& model )noexcept
{
	model.keybuffer = std::queue<Keyboard::Event>();
}

void KbdController::FlushChar( Keyboard& model )noexcept
{
	model.charbuffer = std::queue<char>();
}

void KbdController::Flush( Keyboard& model )noexcept
{
	FlushKey( model );
	FlushChar( model );
}

void KbdController::EnableAutorepeat( Keyboard& model )noexcept
{
	model.autorepeatEnabled = true;
}

void KbdController::DisableAutorepeat( Keyboard& model )noexcept
{
	model.autorepeatEnabled = false;
}

bool KbdController::KeyIsPressed( Keyboard const& model, unsigned char keycode )noexcept
{
	return model.keystates[ keycode ];
}

Keyboard::Event KbdController::ReadKey( Keyboard& model )noexcept
{
	if( model.keybuffer.size() > 0u )
	{
		Keyboard::Event e = model.keybuffer.front();
		model.keybuffer.pop();
		return e;
	}
	else
	{
		return Keyboard::Event();
	}
}

bool KbdController::KeyIsEmpty( Keyboard const& model )noexcept
{
	return model.keybuffer.empty();
}

char KbdController::ReadChar( Keyboard& model )noexcept
{
	if( model.charbuffer.size() > 0u )
	{
		unsigned char charcode = model.charbuffer.front();
		model.charbuffer.pop();
		return charcode;
	}
	else
	{
		return 0;
	}
}

bool KbdController::CharIsEmpty( Keyboard const& model )noexcept
{
	return model.charbuffer.empty();
}

bool KbdController::AutorepeatIsEnabled( Keyboard const& model )noexcept
{
	return model.autorepeatEnabled;
}

void KbdController::OnKeyPressed( Keyboard& model, unsigned char keycode )
{
	model.keystates[ keycode ] = true;
	model.keybuffer.push( Keyboard::Event( Keyboard::Event::Type::Press, keycode ) );
	TrimBuffer( model, model.keybuffer );
}

void KbdController::OnKeyReleased( Keyboard& model, unsigned char keycode )
{
	model.keystates[ keycode ] = false;
	model.keybuffer.push( Keyboard::Event( Keyboard::Event::Type::Release, keycode ) );
	TrimBuffer( model, model.keybuffer );
}

void KbdController::OnChar( Keyboard& model, char character )
{
	model.charbuffer.push( character );
	TrimBuffer( model, model.charbuffer );
}

void KbdController::ClearState( Keyboard& model )noexcept
{
	model.keystates.reset();
}

template<typename T>
void KbdController::TrimBuffer( Keyboard& model, std::queue<T>& buffer )noexcept
{
	while( buffer.size() > Keyboard::bufferSize )
	{
		buffer.pop();
	}
}

