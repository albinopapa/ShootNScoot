#include "Settings.h"
#include "SurfaceController.h"
#include "Window.h"
#include "WindowView.h"


void WindowView::Preset( Window const & model, Surface const& pixel_buffer )
{
	// lock and map the adapter memory for copying over the sysbuffer
	auto mappedSysBufferTexture = D3D11_MAPPED_SUBRESOURCE{};
	if( auto hr = model.pImmediateContext->Map( model.pSysBufferTexture.Get(), 0u,
		D3D11_MAP_WRITE_DISCARD, 0u, &mappedSysBufferTexture ); FAILED( hr ) )
	{
		throw std::system_error(
			std::error_code( hr, std::system_category() ),
			"Mapping sysbuffer"
		);
	}

	// setup parameters for copy operation
	auto* pDst			= reinterpret_cast< Color* >( mappedSysBufferTexture.pData );
	auto const* pSrc	= SurfaceController::Data( pixel_buffer );
	const auto dstPitch = size_t( mappedSysBufferTexture.RowPitch / sizeof( Color ) );
	const auto srcPitch = size_t( sns::viewport_size.width );
	const auto rowBytes = size_t( srcPitch * sizeof( Color ) );

	// perform the copy line-by-line
	for( size_t y = 0u; y < size_t( sns::viewport_size.height ); y++ )
	{
		memcpy( &pDst[ y * dstPitch ], &pSrc[ y * srcPitch ], rowBytes );
	}

	// release the adapter memory
	model.pImmediateContext->Unmap( model.pSysBufferTexture.Get(), 0u );

	// render offscreen scene texture to back buffer
	model.pImmediateContext->IASetInputLayout( model.pInputLayout.Get() );
	model.pImmediateContext->VSSetShader( model.pVertexShader.Get(), nullptr, 0u );
	model.pImmediateContext->PSSetShader( model.pPixelShader.Get(), nullptr, 0u );
	model.pImmediateContext->IASetPrimitiveTopology( D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST );

	constexpr UINT stride = sizeof( Window::FSQVertex );
	constexpr UINT offset = 0u;
	model.pImmediateContext->IASetVertexBuffers( 0u, 1u, model.pVertexBuffer.GetAddressOf(), &stride, &offset );
	model.pImmediateContext->PSSetShaderResources( 0u, 1u, model.pSysBufferTextureView.GetAddressOf() );
	model.pImmediateContext->PSSetSamplers( 0u, 1u, model.pSamplerState.GetAddressOf() );
	model.pImmediateContext->Draw( 6u, 0u );

	// flip back/front buffers
	if( auto hr = model.pSwapChain->Present( 1u, 0u ); FAILED( hr ) )
	{
		if( hr == DXGI_ERROR_DEVICE_REMOVED )
		{
			throw std::system_error(
				std::error_code( model.pDevice->GetDeviceRemovedReason(),
				std::system_category() ), "Presenting back buffer [device removed]"
			);
		}
		else
		{
			throw std::system_error(
				std::error_code( hr, std::system_category() ),
				"Presenting back buffer"
			);
		}
	}
}
