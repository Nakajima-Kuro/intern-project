#include "Conductor.h"
Conductor::Conductor(float bpm, int measures, std::string songPath)
	:SoundServer(songPath)
{
	m_bpm = bpm;
	m_measures = measures;
	m_secPerBeat = 60.0 / bpm;
	m_startTimer = new Timer();
	m_startTimer->Attach(this);
}

Conductor::~Conductor()
{
	m_startTimer->Detach(this);
	m_startTimer->stop();
	if (m_startTimer != nullptr) {
		delete m_startTimer;
	}
	Stop();
}

void Conductor::PlayWithBeatOffset(int offset)
{
	m_beatsBeforeStart = offset;
	m_startTimer->start(m_secPerBeat);
}

void Conductor::PlayFromBeat(int beat, int offset)
{
	m_songPosition = double(beat) / m_bpm * 60.0;
	//seek beat code in here
	m_beatsBeforeStart = offset;
	m_songPositionInBeat = offset;
	m_measure = (beat % m_measures) + 1;
	Play();
	Seek(m_songPosition);
}

void Conductor::Update(float deltaTime)
{
	if (IsPlaying()) {
		m_songPosition = GetPlaybackOffset();
		m_songPositionInBeat = int(floor(m_songPosition / m_secPerBeat)) + m_beatsBeforeStart;
		ReportBeat();
	}
}

void Conductor::Update(const std::string& message_from_subject)
{
	//On StartTimer Timeout
	if (message_from_subject.compare("timeout") == 0) {
		m_songPositionInBeat += 1;
		if (m_songPositionInBeat < m_beatsBeforeStart) {
			ReportBeat();
			m_startTimer->start();
		}
		else {
			delete m_startTimer;
			Play();
		}
	}
}

int Conductor::GetBeat()
{
	return m_songPositionInBeat;
}

int Conductor::GetMeasure()
{
	return m_measure;
}

void Conductor::ReportBeat()
{
	if (m_lastReportBeat < m_songPositionInBeat) {
		if (m_measure > m_measures) {
			m_measure = 1;
		}
		//Emit Signal!!! Hail Godot
		Notify("beat");
		Notify("measure");

		m_lastReportBeat = m_songPositionInBeat;
		m_measure += 1;
	}
}
