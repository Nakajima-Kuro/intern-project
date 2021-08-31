#pragma once
#include "SoundDevice.h"
#include "SoundBuffer.h"
#include "SoundSource.h"
#include "Timer.h"
#include "ISubject.h"
#include <thread>
class Conductor : public ISubject, public IObserver
{
public:
	Conductor(float bpm, int measures, std::string songName);
	~Conductor();
	float m_bpm;
	int m_measures;
	void PlayWithBeatOffset(int offset);
	void PlayFromBeat(int beat, int offset);
	void Pause();
	void Resume();
	
	void Update(float deltaTime);
	void Update(const std::string& message_from_subject) override;

	int GetBeat();
	int GetMeasure();
private:
	//Tracking position of the song
	double m_songPosition = 0.0;
	int m_songPositionInBeat = 1;
	double m_secPerBeat;
	int m_lastReportBeat = 0;
	int m_beatsBeforeStart = 0;
	int m_measure = 1;

	//All OpenAl resources for playback
	SoundDevice* m_soundDevice = SoundDevice::get();
	SoundSource m_soundSource;
	uint32_t /*ALuint*/ m_song;
	std::string m_path = "..\\Data\\Sounds\\";

	//Timer
	Timer* m_startTimer;

	void Play();
	//All the magic in this function
	void ReportBeat();
};

