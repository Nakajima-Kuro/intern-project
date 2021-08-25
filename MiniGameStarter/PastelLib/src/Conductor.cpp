#include "Conductor.h"

Conductor::Conductor(int bpm, int measures, std::string songName)
{
	this->bpm = bpm;
	this->measures = measures;
	this->path.append(songName);
	this->secPerBeat = 60.0 / bpm;
	this->song = SoundBuffer::get()->addSoundEffect(this->path.c_str());
	this->StartTimer = new Timer();
	this->StartTimer->Attach(this);
}

Conductor::~Conductor()
{
}

void Conductor::PlayWithBeatOffset(int offset)
{
	this->beatsBeforeStart = offset;
	this->StartTimer->start(this->secPerBeat);
}

void Conductor::PlayFromBeat(int beat, int offset)
{
	this->Play();
	//seek beat code in here
}

void Conductor::Play()
{
	soundSource.Play(this->song);
}

void Conductor::Update(float deltaTime)
{
	if (AL_PLAYING) {
		this->songPosition = AL_SEC_OFFSET;
		this->songPositionInBeat = int(floor(this->songPosition / this->secPerBeat)) + this->beatsBeforeStart;
		this->ReportBeat();
	}
}

void Conductor::Update(const std::string& message_from_subject)
{
	//On StartTimer Timeout
	if (strcmp(message_from_subject.c_str(), "timeout") == 0) {
		this->songPositionInBeat += 1;
		if (this->songPositionInBeat < this->beatsBeforeStart - 1) {
			this->StartTimer->start();
		}
		else if (this->songPositionInBeat == beatsBeforeStart - 1) {
			//Remember to minus the output latency here, not found on openAL docs yet
			this->StartTimer->start();
		}
		else {
			this->Play();
			this->measure = 1;
			delete StartTimer;
		}
		this->ReportBeat();
	}
}

int Conductor::GetBeat()
{
	return this->songPositionInBeat;
}

int Conductor::GetMeasure()
{
	return this->measure;
}

void Conductor::ReportBeat()
{
	if (this->lastReportBeat < this->songPositionInBeat) {
		if (this->measure > this->measures) {
			measure = 1;
		}
		//Emit Signal!!! Hail Godot
		this->Notify("beat");
		this->Notify("measure");

		this->lastReportBeat = this->songPositionInBeat;
		this->measure += 1;
	}
}
