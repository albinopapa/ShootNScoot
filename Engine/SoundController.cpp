#include "ChiliWin.h"
#include "SoundController.h"
#include "XAudio\XAudio2.h"

#include <algorithm>
#include <cassert>
#include <string>
#include <system_error>

#include <mfapi.h>
#include <mfidl.h>
#include <mfreadwrite.h>
#include <mferror.h>
#include <Propvarutil.h>

void SoundChannelController::PlaySoundBuffer( Channel& model, Sound& s, float freqMod, float vol )
{
	assert( model.pSource && !model.pSound );
	{
		std::lock_guard<std::mutex> lock( s.mutex );
		s.activeChannelPtrs.push_back( &model );
	}
	// callback thread not running yet, so no sync necessary for pSound
	model.pSound = &s;
	model.xaBuffer->pAudioData = s.pData.get();
	model.xaBuffer->AudioBytes = s.nBytes;
	if( s.looping )
	{
		model.xaBuffer->LoopBegin = s.loopStart;
		model.xaBuffer->LoopLength = s.loopEnd - s.loopStart;
		model.xaBuffer->LoopCount = XAUDIO2_LOOP_INFINITE;
	}
	else
	{
		model.xaBuffer->LoopCount = 0u;
	}
	HRESULT hr;
	if( FAILED( hr = model.pSource->SubmitSourceBuffer( model.xaBuffer.get(), nullptr ) ) )
	{
		auto err_code = std::error_code( hr, std::system_category() );
		throw std::system_error( err_code, "Starting playback - submitting source buffer" );
	}
	if( FAILED( hr = model.pSource->SetFrequencyRatio( freqMod ) ) )
	{
		auto err_code = std::error_code( hr, std::system_category() );
		throw std::system_error( err_code, "Starting playback - setting frequency" );
	}
	if( FAILED( hr = model.pSource->SetVolume( vol ) ) )
	{
		auto err_code = std::error_code( hr, std::system_category() );
		throw std::system_error( err_code, "Starting playback - setting volume" );
	}
	if( FAILED( hr = model.pSource->Start() ) )
	{
		auto err_code = std::error_code( hr, std::system_category() );
		throw std::system_error( err_code, "Starting playback - starting" );
	}
}

void SoundChannelController::Stop( Channel& model )
{
	assert( model.pSource && model.pSound );
	model.pSource->Stop();
	model.pSource->FlushSourceBuffers();
}

void SoundChannelController::RetargetSound( Channel& model, const Sound* pOld, Sound* pNew )
{
	assert( pOld == model.pSound );
	model.pSound = pNew;
}

SoundSystem& SoundSystemController::Get()
{
	static SoundSystem instance;
	return instance;
}

void SoundSystemController::SetMasterVolume( float vol )
{
	if( auto hr = Get().pMaster->SetVolume( vol ); FAILED( hr ) )
	{
		auto err_code = std::error_code( hr, std::system_category() );
		throw std::system_error( err_code, "Setting master volume" );
	}
}

const WAVEFORMATEX& SoundSystemController::GetFormat()
{
	return *Get().format;
}

void SoundSystemController::PlaySoundBuffer( Sound & s, float freqMod, float vol )
{
	auto& model = Get();
	std::lock_guard<std::mutex> lock( model.mutex );
	if( model.idleChannelPtrs.size() > 0 )
	{
		model.activeChannelPtrs.push_back( std::move( model.idleChannelPtrs.back() ) );
		model.idleChannelPtrs.pop_back();
		SoundChannelController::PlaySoundBuffer( 
			*model.activeChannelPtrs.back(), s, freqMod, vol 
		);
	}
}

void SoundSystemController::DeactivateChannel( SoundSystem& model, Channel& channel )
{
	auto is_same_channel = [ &channel ]( auto const& pChan )
	{
		return &channel == pChan.get();
	};
	std::lock_guard<std::mutex> lock( model.mutex );

	auto i = std::find_if( 
		model.activeChannelPtrs.begin(), 
		model.activeChannelPtrs.end(),
		is_same_channel
	);

	model.idleChannelPtrs.push_back( std::move( *i ) );
	model.activeChannelPtrs.erase( i );
}

Sound SoundController::LoadNonWav( const std::wstring& fileName, Sound::LoopType loopType,
	unsigned int loopStartSample, unsigned int loopEndSample,
	float loopStartSeconds, float loopEndSeconds )
{
	namespace wrl = Microsoft::WRL;

	// if manual float looping, second inputs cannot be null
	assert( ( loopType == Sound::LoopType::ManualFloat ) !=
		( loopStartSeconds == Sound::nullSeconds || loopEndSeconds == Sound::nullSeconds ) &&
		"Did you pass a LoopType::Manual to the constructor? (BAD!)" );
	// if manual sample looping, sample inputs cannot be null
	assert( ( loopType == Sound::LoopType::ManualSample ) !=
		( loopStartSample == Sound::nullSample || loopEndSample == Sound::nullSample ) &&
		"Did you pass a LoopType::Manual to the constructor? (BAD!)" );
	// load from non-wav cannot use embedded loop points
	assert( loopType != Sound::LoopType::AutoEmbeddedCuePoints &&
		"load from non-wav cannot use embedded loop points" );

	Sound sound;

	// make sure that the sound system is loaded first!
	SoundSystemController::Get();

	// creating source reader
	wrl::ComPtr<IMFSourceReader> pReader;
	if( auto hr = MFCreateSourceReaderFromURL( fileName.c_str(), nullptr, &pReader ); 
		FAILED( hr ) )
	{
		auto err_code = std::error_code( hr, std::system_category() );
		auto filename = std::string( fileName.begin(), fileName.end() );
		throw std::system_error( err_code, "Creating MF Source Reader\nFilename: " + filename );
	}

	// selecting first stream
	if( auto hr = pReader->SetStreamSelection( ( DWORD )MF_SOURCE_READER_ALL_STREAMS, FALSE ); 
		FAILED( hr ) )
	{
		auto err_code = std::error_code( hr, std::system_category() );
		throw std::system_error( err_code, "setting stream selection all" );
	}

	if( auto hr = pReader->SetStreamSelection( ( DWORD )MF_SOURCE_READER_FIRST_AUDIO_STREAM, TRUE ); 
		FAILED( hr ) )
	{
		auto err_code = std::error_code( hr, std::system_category() );
		throw std::system_error( err_code, "setting stream selection first" );
	}


	// Configuring output format
	wrl::ComPtr<IMFMediaType> pUncompressedAudioType;
	{
		wrl::ComPtr<IMFMediaType> pPartialType;

		// configuring partial type
		if( auto hr = MFCreateMediaType( &pPartialType ); FAILED( hr ) )
		{
			auto err_code = std::error_code( hr, std::system_category() );
			throw std::system_error( err_code, "creating partial media type" );
		}

		if( auto  hr = pPartialType->SetGUID( MF_MT_MAJOR_TYPE, MFMediaType_Audio ); 
			FAILED( hr ) )
		{
			auto err_code = std::error_code( hr, std::system_category() );
			throw std::system_error( err_code, "setting partial media type major guid" );
		}

		if( auto hr = pPartialType->SetGUID( MF_MT_SUBTYPE, MFAudioFormat_PCM );
			FAILED( hr ) )
		{
			auto err_code = std::error_code( hr, std::system_category() );
			throw std::system_error( err_code, "setting partial media type sub guid" );
		}

		// Set this type on the source reader. The source reader will
		// load the necessary decoder.
		if( auto hr = pReader->SetCurrentMediaType(
			( DWORD )MF_SOURCE_READER_FIRST_AUDIO_STREAM,
			nullptr, pPartialType.Get() ); FAILED( hr ) )
		{
			auto err_code = std::error_code( hr, std::system_category() );
			throw std::system_error( err_code, "setting partial type on source reader" );
		}

		// Get the complete uncompressed format.
		if( auto hr = pReader->GetCurrentMediaType(
			( DWORD )MF_SOURCE_READER_FIRST_AUDIO_STREAM,
			&pUncompressedAudioType ); FAILED( hr ) )
		{
			auto err_code = std::error_code( hr, std::system_category() );
			throw std::system_error( err_code, "getting complete uncompressed format" );
		}

		// Ensure the stream is selected.
		if( auto hr = pReader->SetStreamSelection(
			( DWORD )MF_SOURCE_READER_FIRST_AUDIO_STREAM,
			TRUE ); FAILED( hr ) )
		{
			auto err_code = std::error_code( hr, std::system_category() );
			throw std::system_error( err_code, 
				"making sure stream is selected (who the fuck knows?)" );
		}
	}

	// calculating number of sample bytes
	// and verifying that format matches sound system channels
	// and setting loop parameters
	{
		UINT32 cbFormat = 0;

		// init smart pointer with custom deleter
		const auto pFormat = [ & ]()
		{
			// to be temp filled with the pointer
			WAVEFORMATEX *pFormat = nullptr;
			// loading format info into wave format structure (callee allocated, but we must free)
			if( auto hr = MFCreateWaveFormatExFromMFMediaType( 
				pUncompressedAudioType.Get(), &pFormat, &cbFormat 
				); FAILED( hr ) )
			{
				auto err_code = std::error_code( hr, std::system_category() );
				throw std::system_error( err_code, 
					"loading format info into wave format structure" );
			}

			return std::unique_ptr<WAVEFORMATEX, decltype( &CoTaskMemFree )>( pFormat, CoTaskMemFree );
		}( );

		// compare format with sound system format
		{
			const auto& sysFormat = SoundSystemController::GetFormat();

			auto filename = std::string( fileName.begin(), fileName.end() );
			if( pFormat->nChannels != sysFormat.nChannels )
			{
				throw std::runtime_error( filename + "bad decompressed wave format (nChannels)" );
			}
			else if( pFormat->wBitsPerSample != sysFormat.wBitsPerSample )
			{
				throw std::runtime_error( filename + "bad decompressed wave format (wBitsPerSample)" );
			}
			else if( pFormat->nSamplesPerSec != sysFormat.nSamplesPerSec )
			{
				throw std::runtime_error( filename + "bad decompressed wave format (nSamplesPerSec)" );
			}
			else if( pFormat->wFormatTag != sysFormat.wFormatTag )
			{
				throw std::runtime_error( filename + "bad decompressed wave format (wFormatTag)" );
			}
			else if( pFormat->nBlockAlign != sysFormat.nBlockAlign )
			{
				throw std::runtime_error( filename + "bad decompressed wave format (nBlockAlign)" );
			}
			else if( pFormat->nAvgBytesPerSec != sysFormat.nAvgBytesPerSec )
			{
				throw std::runtime_error( filename + "bad decompressed wave format (nAvgBytesPerSec)" );
			}
		}

		// get sound buffer byte length
		{
			// inheritance for automatic freeing of propvariant resources
			struct AutoPropVariant : PROPVARIANT
			{
				~AutoPropVariant()
				{
					PropVariantClear( this );
				}
			} var;

			// get duration attribute (as prop variant) from reader
			if( auto  hr = pReader->GetPresentationAttribute( 
				MF_SOURCE_READER_MEDIASOURCE, MF_PD_DURATION, &var ); FAILED( hr ) )
			{
				auto err_code = std::error_code( hr, std::system_category() );
				throw std::system_error( err_code, 
					"getting duration attribute from reader" );
			}

			// getting int64 from duration prop variant
			auto duration = 0ll;
			if( auto hr = PropVariantToInt64( var, &duration ); FAILED( hr ) )
			{
				auto err_code = std::error_code( hr, std::system_category() );
				throw std::system_error( err_code, 
					"getting int64 out of variant property (duration)" );
			}

			// calculating number of bytes for samples (duration is in units of 100ns)
			// (adding extra 1 sec of padding for length calculation error margin)
			sound.nBytes = UINT32( ( pFormat->nAvgBytesPerSec * duration ) / 10000000 + pFormat->nAvgBytesPerSec );
		}

		/////////////////////////////
		// setting looping parameters
		switch( loopType )
		{
			case Sound::LoopType::ManualFloat:
			{
				sound.looping = true;

				const auto& sysFormat = SoundSystemController::GetFormat();
				const auto nFrames = sound.nBytes / sysFormat.nBlockAlign;

				const unsigned int nFramesPerSec = sysFormat.nAvgBytesPerSec / sysFormat.nBlockAlign;
				sound.loopStart = unsigned int( loopStartSeconds * float( nFramesPerSec ) );
				assert( sound.loopStart < nFrames );
				sound.loopEnd = unsigned int( loopEndSeconds * float( nFramesPerSec ) );
				assert( sound.loopEnd > sound.loopStart && sound.loopEnd < nFrames );

				// just in case ;)
				sound.loopStart = std::min( sound.loopStart, nFrames - 1u );
				sound.loopEnd = std::min( sound.loopEnd, nFrames - 1u );
			}
			break;
			case Sound::LoopType::ManualSample:
			{
				sound.looping = true;

				const auto& sysFormat = SoundSystemController::GetFormat();
				const auto nFrames = sound.nBytes / sysFormat.nBlockAlign;

				assert( loopStartSample < nFrames );
				sound.loopStart = loopStartSample;
				assert( loopEndSample > loopStartSample && loopEndSample < nFrames );
				sound.loopEnd = loopEndSample;

				// just in case ;)
				sound.loopStart = std::min( sound.loopStart, nFrames - 1u );
				sound.loopEnd = std::min( sound.loopEnd, nFrames - 1u );
			}
			break;
			case Sound::LoopType::AutoFullSound:
			{
				sound.looping = true;

				const auto nFrames = sound.nBytes / SoundSystemController::GetFormat().nBlockAlign;
				assert( nFrames != 0u && "Cannot auto full-loop on zero-length sound!" );
				sound.loopStart = 0u;
				sound.loopEnd = nFrames != 0u ? nFrames - 1u : 0u;
			}
			break;
			case Sound::LoopType::NotLooping:
				break;
			default:
				assert( "Bad LoopType encountered!" && false );
				break;
		}
		/////////////////////////////
	}

	// allocate memory for sample data
	sound.pData = std::make_unique<BYTE[]>( sound.nBytes );

	// decode samples and copy into data buffer
	size_t nBytesWritten = 0u;
	while( true )
	{
		wrl::ComPtr<IMFSample> pSample;
		DWORD dwFlags = 0;

		// Read the next samples
		if( auto  hr = pReader->ReadSample(
			( DWORD )MF_SOURCE_READER_FIRST_AUDIO_STREAM,
			0, nullptr, &dwFlags, nullptr, &pSample ); FAILED( hr ) )
		{
			auto err_code = std::error_code( hr, std::system_category() );
			throw std::system_error( err_code, "reading next samples" );
		}

		if( dwFlags & MF_SOURCE_READERF_CURRENTMEDIATYPECHANGED )
		{
			throw std::runtime_error( "Type change - not supported by WAVE file format.@ ReadSample" );
		}

		if( dwFlags & MF_SOURCE_READERF_ENDOFSTREAM )
		{
			break;
		}

		if( pSample == nullptr )
		{
			continue;
		}

		// Get a pointer to the audio data in the sample.
		wrl::ComPtr<IMFMediaBuffer> pBuffer;
		if( auto hr = pSample->ConvertToContiguousBuffer( &pBuffer ); FAILED( hr ) )
		{
			auto err_code = std::error_code( hr, std::system_category() );
			throw std::system_error( err_code, "converting to contiguous buffer" );
		}

		BYTE *pAudioData = nullptr;
		DWORD cbBuffer = 0;
		if( auto hr = pBuffer->Lock( &pAudioData, nullptr, &cbBuffer ); FAILED( hr ) )
		{
			auto err_code = std::error_code( hr, std::system_category() );
			throw std::system_error( err_code, "locking sample buffer" );
		}

		// Make sure not to exceed the size of the buffer
		if( nBytesWritten + cbBuffer > sound.nBytes )
		{
			throw std::runtime_error( "too many bytes being decoded wtf??!~" );
		}

		// copy the sample bytes
		memcpy( &sound.pData[ nBytesWritten ], pAudioData, cbBuffer );

		// Update running total of audio data.
		nBytesWritten += cbBuffer;

		// Unlock the buffer.
		if( auto hr = pBuffer->Unlock(); FAILED( hr ) )
		{
			auto err_code = std::error_code( hr, std::system_category() );
			throw std::system_error( err_code, "unlocking sample buffer" );
		}
	}

	// reallocate buffer for proper size
	{
		// allocate buffer
		sound.pData = std::make_unique<BYTE[]>( nBytesWritten );
		// copy over bytes
		memcpy( sound.pData.get(), sound.pData.get(), nBytesWritten );
		// adjust byte count
		sound.nBytes = UINT32( nBytesWritten );
	}

	return sound;
}

void SoundController::Play( Sound& model, float freqMod, float vol )
{
	SoundSystemController::PlaySoundBuffer( model, freqMod, vol );
}

void SoundController::StopOne( Sound& model )
{
	auto lock = std::lock_guard( model.mutex );
	if( !model.activeChannelPtrs.empty() )
	{
		SoundChannelController::Stop( *model.activeChannelPtrs.front() );
	}
}

void SoundController::StopAll( Sound& model )
{
	std::lock_guard<std::mutex> lock( model.mutex );
	for( auto pChannel : model.activeChannelPtrs )
	{
		SoundChannelController::Stop( *pChannel );
	}
}

