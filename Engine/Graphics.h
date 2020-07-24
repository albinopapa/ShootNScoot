/******************************************************************************************
*	Chili DirectX Framework Version 16.07.20											  *
*	Graphics.h																			  *
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

#include "AlphaTextureEffect.h"
#include "ChiliWin.h"
#include "ChiliException.h"
#include "Colors.h"
#include "Mat3.h"
#include "Pipeline.h"
#include "Rect.h"
#include "Surface.h"
#include "Vec2.h"

#include <cassert>
#include <algorithm>

#include <d3d11.h>
#include <wrl.h>

class Graphics
{
public:
	static inline int ScreenWidth = 800;
	static inline int ScreenHeight = 600;

public:
	class Exception : public ChiliException
	{
	public:
		Exception( HRESULT hr,const std::wstring& note,const wchar_t* file,unsigned int line );
		std::wstring GetErrorName() const;
		std::wstring GetErrorDescription() const;
		virtual std::wstring GetFullMessage() const override;
		virtual std::wstring GetExceptionType() const override;
	private:
		HRESULT hr;
	};
private:
	// vertex format for the framebuffer fullscreen textured quad
	struct FSQVertex
	{
		float x,y,z;		// position
		float u,v;			// texcoords
	};

public:
	Graphics( class HWNDKey& key );
	Graphics( const Graphics& ) = delete;
	Graphics& operator=( const Graphics& ) = delete;

	void EndFrame();
	void BeginFrame()noexcept;

	Color GetPixel( int x,int y ) const;
	void PutPixel( int x,int y,Color c );
	void PutPixelClipped( int x, int y, Color color )noexcept;

	static bool IsVisible( RectI const& rect );

	void DrawDisc( Point const& center, int radius, Color color )noexcept;
	void DrawCircle( Point const& center, int radius, Color color )noexcept;
	void DrawRect( RectI const& dst, Color color )noexcept;
	void DrawLine( Point const& p0, Point const& p2, Color color )noexcept;

	template<typename Effect>
	void DrawSprite( RectI const& dst, Radian angle, Surface const& sprite, Effect&& effect )noexcept {
		const auto ratio = static_cast< float >( dst.Height() ) / static_cast< float >( dst.Width() );
		const auto quad = RectF::FromCenter( Vec2{}, SizeF{ 1.f, ratio } *.5f );

		auto pl = Pipeline{ effect, pSysBuffer };
		pl.PSSetTexture( sprite );
		pl.vertices[ 0 ] = { { quad.left, quad.top }, { 0.f, 0.f } };
		pl.vertices[ 1 ] = { { quad.right, quad.top }, { 1.f, 0.f } };
		pl.vertices[ 2 ] = { { quad.left, quad.bottom }, { 0.f, 1.f } };
		pl.vertices[ 3 ] = { { quad.right, quad.bottom }, { 1.f, 1.f } };
		pl.Draw( dst, angle );
	}

	template<typename T>
	static Rect_<T> GetRect()noexcept {
		return{
			static_cast< T >( 0 ),
			static_cast< T >( 0 ),
			static_cast< T >( ScreenWidth ),
			static_cast< T >( ScreenHeight )
		};
	}
	~Graphics();
private:
	Microsoft::WRL::ComPtr<IDXGISwapChain>				pSwapChain;
	Microsoft::WRL::ComPtr<ID3D11Device>				pDevice;
	Microsoft::WRL::ComPtr<ID3D11DeviceContext>			pImmediateContext;
	Microsoft::WRL::ComPtr<ID3D11RenderTargetView>		pRenderTargetView;
	Microsoft::WRL::ComPtr<ID3D11Texture2D>				pSysBufferTexture;
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView>	pSysBufferTextureView;
	Microsoft::WRL::ComPtr<ID3D11PixelShader>			pPixelShader;
	Microsoft::WRL::ComPtr<ID3D11VertexShader>			pVertexShader;
	Microsoft::WRL::ComPtr<ID3D11Buffer>				pVertexBuffer;
	Microsoft::WRL::ComPtr<ID3D11InputLayout>			pInputLayout;
	Microsoft::WRL::ComPtr<ID3D11SamplerState>			pSamplerState;
	D3D11_MAPPED_SUBRESOURCE							mappedSysBufferTexture;
	Surface                                             pSysBuffer;
};
