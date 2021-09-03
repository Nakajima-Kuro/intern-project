#include "SoundServer.h"
#include <thread>

SoundServer::SoundServer(std::string path)
{
	m_path = path;
	m_song = SoundBuffer::get()->addSoundEffect(m_path.c_str());
}

SoundServer::~SoundServer()
{
	SoundBuffer::get()->removeSoundEffect(m_song);
}

void SoundServer::Play()
{
	auto thread = std::thread(&SoundServer::PlaySound, this);
	thread.detach();
}

void SoundServer::Pause()
{
	m_soundSource.Pause();
}

void SoundServer::Resume()
{
	m_soundSource.Resume();
}

void SoundServer::Stop()
{
	m_soundSource.Stop();
}

void SoundServer::Seek(float second)
{
	m_soundSource.Seek(second);
}

double SoundServer::GetPlaybackOffset()
{
	return m_soundSource.GetPlaybackOffset();
}

bool SoundServer::IsPlaying()
{
	return m_soundSource.IsPlaying();
}

void SoundServer::PlaySound()
{
	m_soundSource.Play(m_song);
}
