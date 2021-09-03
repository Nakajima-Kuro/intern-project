#pragma once
#include "SoundDevice.h"
#include "SoundBuffer.h"
#include "SoundSource.h"
#include "Timer.h"
#include "ISubject.h"
#include "SoundServer.h"
#include <thread>
class Conductor : public SoundServer, public ISubject, public IObserver
{
public:
	Conductor(float bpm, int measures, std::string songPath);
	~Conductor();
	void PlayWithBeatOffset(int offset);
	void PlayFromBeat(int beat, int offset);
	void Pause();
	void Resume();
	
	void Update(float deltaTime);
	void Update(const std::string& message_from_subject) override;

	int GetBeat();
	int GetMeasure();
private:
	float m_bpm;
	int m_measures;
	//Tracking position of the song
	double m_songPosition = 0.0;
	int m_songPositionInBeat = 1;
	double m_secPerBeat;
	int m_lastReportBeat = 0;
	int m_beatsBeforeStart = 0;
	int m_measure = 1;

	//Timer
	Timer* m_startTimer;

	//All the magic in this function
	void ReportBeat();
};

