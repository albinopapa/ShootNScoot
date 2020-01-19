#include "App.h"

App::App( const wchar_t* pArgs )
	:
	window( *this ),
	game( *this ),
	args( pArgs )
{}
