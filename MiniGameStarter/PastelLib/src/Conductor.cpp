#include "Conductor.h"
Conductor::Conductor(float bpm, int measures, std::string songPath)
{
	m_bpm = bpm;
	m_measures = measures;
	m_path.append(songPath);
	m_secPerBeat = 60.0 / bpm;
	m_song = SoundBuffer::get()->addSoundEffect(m_path.c_str());
	m_startTimer = new Timer();
	m_startTimer->Attach(this);
}

Conductor::~Conductor()
{
	if (m_startTimer != nullptr) {
		delete m_startTimer;
	}
	m_soundSource.Stop();
	SoundBuffer::get()->removeSoundEffect(m_song);
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
	m_measure = beat % m_measures;
	m_startTimer->start(0);
}

void Conductor::Play()
{
	m_soundSource.Play(m_song, int(m_songPosition));
}

void Conductor::Pause()
{
	m_soundSource.Pause();
}

void Conductor::Resume()
{
	m_soundSource.Resume();
}

void Conductor::Update(float deltaTime)
{
	if (m_soundSource.IsPlaying()) {
		m_songPosition = m_soundSource.GetPlaybackOffset();
		m_songPositionInBeat = int(floor(m_songPosition / m_secPerBeat)) + m_beatsBeforeStart;
		ReportBeat();
	}
}

void Conductor::Update(const std::string& message_from_subject)
{
	//On StartTimer Timeout
	if (message_from_subject.compare("timeout") == 0) {
		m_songPositionInBeat += 1;
		if (m_songPositionInBeat < m_beatsBeforeStart - 1) {
			m_startTimer->start();
		}
		else if (m_songPositionInBeat == m_beatsBeforeStart - 1) {
			//Remember to minus the output latency here, not found on openAL docs yet
			m_startTimer->start();
		}
		else {
			Play();
			m_measure = 1;
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
