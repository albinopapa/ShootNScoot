#pragma once

#include "Sound.h"

class SoundChannelController
{
public:
	static void PlaySoundBuffer( Channel& model, class Sound& s, float freqMod, float vol );
	static void Stop( Channel& model );
private:
	friend class Sound;
	static void RetargetSound( Channel& model, const Sound* pOld, Sound* pNew );
};

class SoundSystemController
{
public:
	static SoundSystem& Get();
	static void SetMasterVolume( float vol = 1.0f );
	static const WAVEFORMATEX& GetFormat();
	static void PlaySoundBuffer( class Sound& s, float freqMod, float vol );

private:
	friend class Channel;
	friend class VoiceCallback;
	static void DeactivateChannel( SoundSystem& model, Channel& channel );

};
class SoundController
{
public:
	static void Play( Sound& model, float freqMod = 1.0f, float vol = 1.0f );
	static void StopOne( Sound& model );
	static void StopAll( Sound& model );
	static Sound LoadNonWav( const std::wstring& fileName, Sound::LoopType loopType,
		unsigned int loopStartSample, unsigned int loopEndSample,
		float loopStartSeconds, float loopEndSeconds );

};