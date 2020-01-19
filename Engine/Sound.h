/****************************************************************************************** 
 *	Chili DirectX Framework Sound Pack Version 16.11.11									  *	
 *	Sound.h																				  *
 *	Copyright 2016 PlanetChili.net <http://www.planetchili.net>							  *
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
 *	along with this source code.  If not, see <http://www.gnu.org/licenses/>.			  *
 ******************************************************************************************/
#pragma once

#include "ChiliException.h"
#include "ChiliWin.h"
#include "COMInitializer.h"
#include <condition_variable>
#include <memory>
#include <mutex>
#include <thread>
#include <vector>
#include <wrl\client.h>

// forward declare WAVEFORMATEX so we don't have to include bullshit headers
struct tWAVEFORMATEX;
typedef tWAVEFORMATEX WAVEFORMATEX;

class Sound;
class SoundSystem;

class Channel
{
	friend class Sound;
	friend class SoundChannelController;
	friend class VoiceCallback;
public:
	Channel( SoundSystem& sys );
	Channel( const Channel& ) = delete;
	~Channel();
private:
	std::unique_ptr<struct XAUDIO2_BUFFER> xaBuffer;
	struct IXAudio2SourceVoice* pSource = nullptr;
	class Sound* pSound = nullptr;
};

class SoundSystem
{
public:
	class APIException : public ChiliException
	{
	public:
		APIException( HRESULT hr, const wchar_t * file, unsigned int line, const std::wstring& note );
		std::wstring GetErrorName() const;
		std::wstring GetErrorDescription() const;
		virtual std::wstring GetFullMessage() const override;
		virtual std::wstring GetExceptionType() const override;
	private:
		HRESULT hr;
	};
	class FileException : public ChiliException
	{
	public:
		FileException( const wchar_t* file,unsigned int line,const std::wstring& note,const std::wstring& filename );
		virtual std::wstring GetFullMessage() const override;
		virtual std::wstring GetExceptionType() const override;
	private:
		std::wstring filename;
	};
private:
	SoundSystem( const SoundSystem& ) = delete;
	SoundSystem();
private:
	friend class Channel;
	friend class SoundSystemController;

	std::vector<std::unique_ptr<Channel>> idleChannelPtrs;
	std::vector<std::unique_ptr<Channel>> activeChannelPtrs;
	Microsoft::WRL::ComPtr<struct IXAudio2> pEngine;
	struct IXAudio2MasteringVoice* pMaster = nullptr;
	std::unique_ptr<WAVEFORMATEX> format;
	std::mutex mutex;
	COMInitializer comInit;
private:
	// change these values to match the format of the wav files you are loading
	// all wav files must have the same format!! (no mixing and matching)
	static constexpr WORD nChannelsPerSound = 2u;
	static constexpr DWORD nSamplesPerSec = 44100u;
	static constexpr WORD nBitsPerSample = 16u;
	// change this value to increase/decrease the maximum polyphony	
	static constexpr size_t nChannels = 64u;
};

class Sound
{
public:
	enum class LoopType
	{
		NotLooping,
		AutoEmbeddedCuePoints,
		AutoFullSound,
		ManualFloat,
		ManualSample,
		Invalid
	};
public:
	Sound() = default;
	// for backwards compatibility--2nd parameter false -> NotLooping (does not work with non-wav)
	Sound( const std::wstring& fileName,bool loopingWithAutoCueDetect );
	// do not pass this function Manual LoopTypes!
	Sound( const std::wstring& fileName,LoopType loopType = LoopType::NotLooping );
	Sound( const std::wstring& fileName,unsigned int loopStart,unsigned int loopEnd );
	Sound( const std::wstring& fileName,float loopStart,float loopEnd );
	Sound( Sound&& donor );
	Sound& operator=( Sound&& donor );
	~Sound();
private:
	Sound( const std::wstring& fileName,LoopType loopType,
		unsigned int loopStartSample,unsigned int loopEndSample,
		float loopStartSeconds,float loopEndSeconds );
private:
	friend class Channel;
	friend class SoundController;
	friend class SoundChannelController;
	friend class VoiceCallback;

	UINT32 nBytes = 0u;
	bool looping = false;
	unsigned int loopStart;
	unsigned int loopEnd;
	std::unique_ptr<BYTE[]> pData;
	std::mutex mutex;
	std::condition_variable cvDeath;
	std::vector<Channel*> activeChannelPtrs;
	static constexpr auto nullSample = 0xFFFFFFFFu;
	static constexpr auto nullSeconds = -1.0f;
};