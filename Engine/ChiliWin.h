/******************************************************************************************
*	Chili DirectX Framework Version 16.07.20											  *
*	ChiliWin.h																			  *
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

// target Windows 7 or later
#define _WIN32_WINNT 0x0601
#include <sdkddkver.h>
// The following #defines disable a bunch of unused windows stuff. If you 
// get weird errors when trying to do some windows stuff, try removing some
// (or all) of these defines (it will increase build time though).
#define WIN32_LEAN_AND_MEAN
#define NOGDICAPMASKS
#define NOSYSMETRICS
#define NOMENUS
#define NOICONS
#define NOSYSCOMMANDS
#define NORASTEROPS
#define OEMRESOURCE
#define NOATOM
#define NOCLIPBOARD
#define NOCOLOR
#define NOCTLMGR
#define NODRAWTEXT
#define NOKERNEL
#define NONLS
#define NOMEMMGR
#define NOMETAFILE
#define NOMINMAX
#define NOOPENFILE
#define NOSCROLL
#define NOSERVICE
#define NOSOUND
#define NOTEXTMETRIC
#define NOWH
#define NOCOMM
#define NOKANJI
#define NOHELP
#define NOPROFILER
#define NODEFERWINDOWPOS
#define NOMCX
#define NORPC
#define NOPROXYSTUB
#define NOIMAGE
#define NOTAPE

#define STRICT

#include <string>
#include <system_error>

#include <Windows.h>
// Windows helpers
#include <windowsx.h>
// Direct2D version 1.0
#include <d2d1.h>
// Direct3D version 1.0
#include <d3d11.h>
// DirectWrite version 1.0
#include <dwrite.h>
// Windows Multimedia for loading audio files
#include <mmreg.h>
// DirectSound for playing files
#include <dsound.h>
// Windows Imaging Codec
#include <wincodec.h>
// Windows Runtime Library helpers - used for ComPtr
#include <wrl/client.h>
// XBox Input API for xbox controllers
#include <Xinput.h>

#pragma comment(lib, "d2d1.lib")
#pragma comment(lib, "d3d11.lib" )
#pragma comment(lib, "dsound.lib")
#pragma comment(lib, "dxguid.lib")
#pragma comment(lib, "dwrite.lib")
#pragma comment(lib, "windowscodecs.lib")
#pragma comment(lib, "winmm.lib" )

class system_error_exception : public std::system_error
{
public:
	system_error_exception( HRESULT hr, const char* filename, int line_number )noexcept
		:
		std::system_error(
			std::error_code( hr, std::system_category() ),
			"Error in file: " + std::string( filename ) + "\n" +
			"Error at line: " + std::to_string( line_number ) + "\n" )
	{}

};

#define ThrowSystemErrorIf( hr )\
if(FAILED((hr))) throw system_error_exception( ( hr ), __FILE__, __LINE__ )
