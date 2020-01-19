#include "App.h"
#include "AppController.h"
#include "AppView.h"
#include "COMInitializer.h"
#include "FrameTimer.h"
#include "Game.h"
#include "GameView.h"
#include "GameController.h"

int WINAPI wWinMain( HINSTANCE hInst,HINSTANCE,LPWSTR pArgs,INT )
{
	try
	{
		auto app = App( pArgs );
		while( AppController::ProcessMessage() )
		{
			AppController::Update( app );
			AppView::Draw( app );
		}
	}
	catch( const std::exception& e )
	{
		// need to convert std::exception what() string from narrow to wide string
		const std::string whatStr( e.what() );
		const std::wstring eMsg = std::wstring( whatStr.begin(),whatStr.end() ) +
			L"\n\nException caught at main window creation.";
		MessageBox( nullptr,eMsg.c_str(),L"Unhandled STL Exception",MB_ICONERROR );
	}
	catch( ... )
	{
		MessageBox( nullptr,L"\n\nException caught at main window creation.",
			L"Unhandled Non-STL Exception",MB_ICONERROR );
	}

	return 0;
}