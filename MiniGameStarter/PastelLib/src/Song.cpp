#include "Song.h"
#include <fstream>
Song::Song(std::string songPath)
	:m_songPath(songPath), m_bpm(0), m_measures(0), m_difficulty(0), m_beatOffset(0)
{
	Init();
}
Song::~Song()
{
	m_beatMap.clear();
}
void Song::Init()
{
	//Load the song and the beat map
	std::ifstream fin;
	fin.open(m_songPath + ".txt");
	if (fin.is_open()) {
		std::getline(fin, m_name);
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
}
std::string Song::GetName()
{
	return m_name;
}
float Song::GetBpm()
{
	return m_bpm;
}

int Song::GetMeasures()
{
	return m_measures;
}

int Song::GetDifficulty()
{
	return m_difficulty;
}

int Song::GetBeatOffset()
{
	return m_beatOffset;
}

std::vector<std::vector<int>> Song::GetBeatMap()
{
	return m_beatMap;
}

std::string Song::GetPath()
{
	return m_songPath;
}
