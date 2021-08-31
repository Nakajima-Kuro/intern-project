#include "Song.h"
#include "Conductor.h"

float Song::GetBpm()
{
	return m_bpm;
}

void Song::SetBpm(float bpm)
{
	m_bpm = bpm;
}

int Song::GetMeasures()
{
	return m_measures;
}

void Song::SetMeasures(int measures)
{
	m_measures = measures;
}

int Song::GetDifficulty()
{
	return m_difficulty;
}

void Song::SetDifficulty(int difficulty)
{
	m_difficulty = difficulty;
}

int Song::GetBeatOffset()
{
	return m_beatOffset;
}

void Song::SetBeatOffset(int beatOffset)
{
	m_beatOffset = beatOffset;
}

Conductor* Song::GetConductor()
{
	return m_conductor;
}

void Song::SetConductor(Conductor* conductor)
{
	m_conductor = conductor;
}

std::vector<std::vector<int>> Song::GetBeatMap()
{
	return m_beatMap;
}

void Song::SetBeatMap(std::vector<std::vector<int>> beatMap)
{
	m_beatMap = beatMap;
}
