#include "Song.h"
#include "Conductor.h"
#include <fstream>
Song::Song(std::string songPath)
	:m_songPath(songPath), m_bpm(0), m_measures(0), m_difficulty(0), m_beatOffset(0), m_conductor(nullptr)
{
	Init();
}
Song::~Song()
{
	delete m_conductor;
	m_beatMap.clear();
}
void Song::Init()
{
	//Load the song and the beat map
	std::ifstream fin;
	fin.open(m_songPath + ".txt");
	if (fin.is_open()) {
		fin >> m_bpm >> m_measures >> m_difficulty >> m_beatOffset;
		std::vector<int> mapPhase;
		std::string line;
		while (fin >> line)
		{
			int start = 0;
			int end = line.find(",");
			while (end != -1) {
				mapPhase.push_back(std::stoi(line.substr(start, end - start)));
				start = end + 1;
				end = line.find(",", start);
			}
			mapPhase.push_back(std::stoi(line.substr(start, end - start)));
			m_beatMap.push_back(mapPhase);
			mapPhase.clear();
		}
		fin.close();
	}

	//Init the conductor
	m_conductor = new Conductor(m_bpm, m_measures, m_songPath + ".wav");
}
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
