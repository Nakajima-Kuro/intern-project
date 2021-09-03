#pragma once
#include "SoundDevice.h"
#include "SoundBuffer.h"
#include "SoundSource.h"
#include <string>
class SoundServer
{
public:
	SoundServer(std::string path);
	virtual ~SoundServer();

	//Sound Control
	void Play();
	void Pause();
	void Resume();
	void Stop();
	void Seek(float second);
	void ChangeSound(std::string path);

	//Info Log
	double GetPlaybackOffset();
	bool IsPlaying();
private:
	//All OpenAl resources for playback
	SoundDevice* m_soundDevice = SoundDevice::get();
	SoundSource m_soundSource;
	uint32_t /*ALuint*/ m_song;
	std::string m_path = "";
	void PlaySound();
};

