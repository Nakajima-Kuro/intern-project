#pragma once
#include "SoundDevice.h"
#include "SoundBuffer.h"
#include "SoundSource.h"
#include "Timer.h"
#include "ISubject.h"
class Conductor : public ISubject, public IObserver
{
public:
	Conductor(int bpm, int measures, std::string songName);
	~Conductor();
	int bpm;
	int measures;
	void PlayWithBeatOffset(int offset);
	void PlayFromBeat(int beat, int offset);
	
	void Update(float deltaTime);
	void Update(const std::string& message_from_subject) override;

	int GetBeat();
	int GetMeasure();
private:
	//Tracking position of the song
	double songPosition = 0.0;
	int songPositionInBeat = 1;
	double secPerBeat;
	int lastReportBeat = 0;
	int beatsBeforeStart = 0;
	int measure = 1;

	//All OpenAl resources for playback
	SoundDevice* soundDevice = SoundDevice::get();
	SoundSource soundSource;
	uint32_t /*ALuint*/ song;
	std::string path = "..\\Data\\Sounds\\";

	//Timer
	Timer* StartTimer;

	void Play();
	//All the magic in this function
	void ReportBeat();
};

