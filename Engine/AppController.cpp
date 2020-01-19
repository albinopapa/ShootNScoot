#include "AppController.h"
#include "FrameTimer.h"
#include "GameController.h"
#include "GameView.h"
#include "KbdController.h"
#include "MouseController.h"
#include "Settings.h"
#include "SurfaceController.h"

void AppController::Update( App & model )
{
	GameController::Update( model.game );
}

void AppController::Kill() noexcept
{
	PostQuitMessage( 0 );
}

bool AppController::ProcessMessage()
{
	MSG msg;
	while( PeekMessage( &msg, nullptr, 0, 0, PM_REMOVE ) )
	{
		TranslateMessage( &msg );
		DispatchMessage( &msg );
		if( msg.message == WM_QUIT )
		{
			return false;
		}
	}
	return true;
}

LRESULT WINAPI AppController::_HandleMsgSetup( HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam )
{
	// use create parameter passed in from CreateWindow() to store window class pointer at WinAPI side
	if( msg == WM_NCCREATE )
	{
		// extract ptr to window class from creation data
		const CREATESTRUCTW* const pCreate = reinterpret_cast< CREATESTRUCTW* >( lParam );
		App& app = *reinterpret_cast< App* >( pCreate->lpCreateParams );
		
		// set WinAPI-managed user data to store ptr to window class
		SetWindowLongPtr( hWnd, GWLP_USERDATA, reinterpret_cast< LONG_PTR >( &app ) );
		
		// set message proc to normal (non-setup) handler now that setup is finished
		SetWindowLongPtr( hWnd, GWLP_WNDPROC, reinterpret_cast< LONG_PTR >( &AppController::_HandleMsgThunk ) );
		
		// forward message to window class handler
		return HandleMsg( app, hWnd, msg, wParam, lParam );
	}
	// if we get a message before the WM_NCCREATE message, handle with default handler
	return DefWindowProc( hWnd, msg, wParam, lParam );
}

LRESULT WINAPI AppController::_HandleMsgThunk( HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam )
{
	// retrieve ptr to window class
	App& app = *reinterpret_cast< App* >( GetWindowLongPtr( hWnd, GWLP_USERDATA ) );
	// forward message to window class handler
	return HandleMsg( app, hWnd, msg, wParam, lParam );
}

LRESULT AppController::HandleMsg( App& model, HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam )
{
	switch( msg )
	{
		case WM_DESTROY:
			Kill();
			break;
		case WM_KILLFOCUS:
			KbdController::ClearState( model.kbd );
			break;

			// ************ KEYBOARD MESSAGES ************ //
		case WM_KEYDOWN:
			// no thank you on the autorepeat
			if( !( lParam & 0x40000000 ) || 
				KbdController::AutorepeatIsEnabled( model.kbd ) ) 
			{
				KbdController::OnKeyPressed( model.kbd, static_cast< unsigned char >( wParam ) );
			}
			break;
		case WM_KEYUP:
			KbdController::OnKeyReleased( model.kbd, static_cast< unsigned char >( wParam ) );
			break;
		case WM_CHAR:
			KbdController::OnChar( model.kbd, static_cast< unsigned char >( wParam ) );
			break;
			// ************ END KEYBOARD MESSAGES ************ //

			// ************ MOUSE MESSAGES ************ //
		case WM_MOUSEMOVE:
		{
			
			if( auto pt = MAKEPOINTS( lParam );
				pt.x > 0 && pt.x < short( sns::viewport_size.width ) &&
				pt.y > 0 && pt.y < short( sns::viewport_size.height ) )
			{
				MouseController::OnMouseMove( model.mouse, pt.x, pt.y );
				if( !MouseController::IsInWindow( model.mouse ) )
				{
					SetCapture( hWnd );
					MouseController::OnMouseEnter( model.mouse );
				}
			}
			else
			{
				if( wParam & ( MK_LBUTTON | MK_RBUTTON ) )
				{
					pt.x = std::max( short( 0 ), pt.x );
					pt.x = std::min( short( sns::viewport_size.width - 1.f ), pt.x );
					pt.y = std::max( short( 0 ), pt.y );
					pt.y = std::min( short( sns::viewport_size.height - 1.f ), pt.y );
					MouseController::OnMouseMove( model.mouse, pt.x, pt.y );
				}
				else
				{
					ReleaseCapture();
					MouseController::OnMouseLeave( model.mouse );
					MouseController::OnLeftReleased( model.mouse, pt.x, pt.y );
					MouseController::OnRightReleased( model.mouse, pt.x, pt.y );
				}
			}
			break;
		}
		case WM_LBUTTONDOWN:
		{
			const auto pt = MAKEPOINTS( lParam );
			MouseController::OnLeftPressed( model.mouse, pt.x, pt.y );
			SetForegroundWindow( hWnd );
			break;
		}
		case WM_RBUTTONDOWN:
		{
			const auto pt = MAKEPOINTS( lParam );
			MouseController::OnRightPressed( model.mouse, pt.x, pt.y );
			break;
		}
		case WM_LBUTTONUP:
		{
			const auto pt = MAKEPOINTS( lParam );
			MouseController::OnLeftReleased( model.mouse, pt.x, pt.y );
			break;
		}
		case WM_RBUTTONUP:
		{
			const auto pt = MAKEPOINTS( lParam );
			MouseController::OnRightReleased( model.mouse, pt.x, pt.y );
			break;
		}
		case WM_MOUSEWHEEL:
		{
			const auto pt = MAKEPOINTS( lParam );
			if( GET_WHEEL_DELTA_WPARAM( wParam ) > 0 )
			{
				MouseController::OnWheelUp( model.mouse, pt.x, pt.y );
			}
			else if( GET_WHEEL_DELTA_WPARAM( wParam ) < 0 )
			{
				MouseController::OnWheelDown( model.mouse, pt.x, pt.y );
			}
			break;
		}
		// ************ END MOUSE MESSAGES ************ //
	}

	return DefWindowProc( hWnd, msg, wParam, lParam );
}

