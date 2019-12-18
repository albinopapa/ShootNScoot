#pragma once

#include "ChiliWin.h"

#include <cassert>
#include <cstdint>
#include <memory>

class Wic
{
public:
	Wic()
	{
		ThrowSystemErrorIf( CoCreateInstance(
			CLSID_WICImagingFactory,
			nullptr,
			CLSCTX_INPROC_SERVER,
			IID_PPV_ARGS( &m_factory )
		) );
	}
	auto create_stream( std::wstring filename )
	{
		assert( !filename.empty() );

		auto stream = Microsoft::WRL::ComPtr<IWICStream>{};
		ThrowSystemErrorIf( m_factory->CreateStream( &stream ) );
		ThrowSystemErrorIf( stream->InitializeFromFilename( filename.c_str(), GENERIC_WRITE ) );

		return stream;
	};
	auto create_encoder( IWICStream* stream )
	{
		assert( stream != nullptr );

		auto encoder = Microsoft::WRL::ComPtr<IWICBitmapEncoder>{};
		ThrowSystemErrorIf( m_factory->CreateEncoder( GUID_ContainerFormatPng, NULL, &encoder ) );
		ThrowSystemErrorIf( encoder->Initialize( stream, WICBitmapEncoderNoCache ) );

		return encoder;
	};
	auto create_frame_encode( IWICBitmapEncoder* pEncoder )
	{
		assert( pEncoder != nullptr );

		auto propertyBag = Microsoft::WRL::ComPtr<IPropertyBag2>{};
		auto frame = Microsoft::WRL::ComPtr<IWICBitmapFrameEncode>{};
		ThrowSystemErrorIf( pEncoder->CreateNewFrame( &frame, &propertyBag ) );
		ThrowSystemErrorIf( frame->Initialize( propertyBag.Get() ) );

		return frame;
	};
	void write_pixels_to_file(
		std::uint32_t width,
		std::uint32_t height,
		std::uint8_t* pixels,
		IWICBitmapEncoder* pEncoder,
		IWICBitmapFrameEncode* pFrame )
	{
		assert( width != 0u );
		assert( height != 0u );
		assert( pixels != nullptr );
		assert( pEncoder != nullptr );
		assert( pFrame != nullptr );

		ThrowSystemErrorIf( pFrame->SetSize( width, height ) );

		auto formatGUID = GUID_WICPixelFormat32bppPBGRA;
		ThrowSystemErrorIf( pFrame->SetPixelFormat( &formatGUID ) );

		auto const cbStride = width * 4u;
		auto const cbBufferSize = height * cbStride;

		ThrowSystemErrorIf( pFrame->WritePixels( height, cbStride, cbBufferSize, pixels ) );
		ThrowSystemErrorIf( pFrame->Commit() );
		ThrowSystemErrorIf( pEncoder->Commit() );
	};
	auto create_decoder( std::wstring filename )
	{
		assert( !filename.empty() );

		auto decoder = Microsoft::WRL::ComPtr<IWICBitmapDecoder>{};
		ThrowSystemErrorIf( m_factory->CreateDecoderFromFilename(
			filename.c_str(),
			nullptr,
			GENERIC_READ,
			WICDecodeMetadataCacheOnLoad,
			&decoder
		) );

		return decoder;
	}
	auto create_frame_decode( IWICBitmapDecoder* pDecoder )
	{
		assert( pDecoder != nullptr );

		auto frame = Microsoft::WRL::ComPtr<IWICBitmapFrameDecode>{};
		ThrowSystemErrorIf( pDecoder->GetFrame( 0, &frame ) );

		return frame;
	}
	auto create_format_converter( IWICBitmapFrameDecode* pFrame )
	{
		assert( pFrame != nullptr );

		auto converter = Microsoft::WRL::ComPtr<IWICFormatConverter>{};
		ThrowSystemErrorIf( m_factory->CreateFormatConverter( &converter ) );
		ThrowSystemErrorIf( converter->Initialize(
			pFrame,
			GUID_WICPixelFormat32bppPBGRA,
			WICBitmapDitherTypeNone,
			nullptr,
			1.0,
			WICBitmapPaletteTypeCustom
		) );

		return converter;
	}
	auto copy_pixels_to_buffer( std::uint32_t width, std::uint32_t height, IWICFormatConverter* pConverter )
	{

		assert( pConverter != nullptr );
		assert( width != 0u );
		assert( height != 0u );

		auto const stride = width * sizeof( uint32_t );
		auto const buffer_size = width * sizeof( uint32_t ) * height;
		auto pixels = std::make_unique<std::uint8_t[]>( buffer_size );

		ThrowSystemErrorIf( pConverter->CopyPixels( nullptr, stride, buffer_size, pixels.get() ) );

		return pixels;
	}
	auto create_bitmap( std::uint32_t width_, std::uint32_t height_ )
	{
		auto bitmap = Microsoft::WRL::ComPtr<IWICBitmap>{};

		ThrowSystemErrorIf( m_factory->CreateBitmap(
			width_,
			height_,
			GUID_WICPixelFormat32bppPBGRA,
			WICBitmapCacheOnDemand,
			&bitmap
		) );

		return bitmap;
	}
	// Assumes a pixel element is 4 bytes or 32 bits per pixel and BGRA order
	auto create_bitmap_from_memory(
		std::uint32_t width_,
		std::uint32_t height_,
		std::unique_ptr<std::uint8_t[]> pixel_data_ )
	{
		assert( width_ > 0 );
		assert( height_ > 0 );
		assert( pixel_data_ != nullptr );

		auto bitmap = Microsoft::WRL::ComPtr<IWICBitmap>{};
		m_factory->CreateBitmapFromMemory(
			width_,
			height_,
			GUID_WICPixelFormat32bppPBGRA,
			width_ * 4,
			width_ * height_ * 4,
			pixel_data_.get(),
			&bitmap
		);
	}
	auto create_bitmap_from_source( IWICBitmapSource* source_ )const
	{
		auto bitmap = Microsoft::WRL::ComPtr<IWICBitmap>{};

		ThrowSystemErrorIf( m_factory->CreateBitmapFromSource(
			source_,
			WICBitmapCacheOnDemand,
			&bitmap
		) );

		return bitmap;
	}
private:
	template<typename ElementType, typename SizeType>
	constexpr SizeType calculate_stride( SizeType width_ )noexcept
	{
		return width_ * SizeType{ sizeof( ElementType ) };
	}

private:
	Microsoft::WRL::ComPtr<IWICImagingFactory> m_factory;
};
