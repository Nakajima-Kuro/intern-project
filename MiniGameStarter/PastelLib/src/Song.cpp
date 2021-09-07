#include "Song.h"
#include <fstream>
Song::Song(std::string songPath)
	:m_songPath(songPath), m_bpm(0), m_measures(0), m_difficulty(0), m_beatOffset(0), m_highscore(0), m_maxCombo(0), m_rank("")
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
			if (end == -1) {
				m_highscore = std::stoi(line);
				break;
			}
			while (end != -1) {
				mapPhase.push_back(std::stoi(line.substr(start, end - start)));
				start = end + 1;
				end = line.find(",", start);
			}
			m_beatMap.push_back(mapPhase);
			mapPhase.clear();
		}
		if (fin.peek() != EOF) {
			fin >> m_maxCombo >> m_rank;
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

int Song::GetMaxCombo()
{
	return m_maxCombo;
}

int Song::GetHighScore()
{
	return m_highscore;
}

std::string Song::GetRank()
{
	return m_rank;
}

void Song::SaveHighScore(int highscore, int maxCombo, std::string rank)
{
	std::string file_name = m_songPath + ".txt";

	std::ifstream fin(m_songPath + ".txt");
	std::ofstream fout;
	fout.open("temp.txt", std::ios::out);

	std::string line;
	for (int i = 0; i < 5; i++) {
		//Read first 5 line: song name, m_bpm, m_measures, m_difficulty, m_beatOffset
		std::getline(fin, line);
		fout << line << "\n";
	}
	while (fin >> line)
	{
		//Read beat map
		int start = 0;
		int end = line.find(",");
		if (end != -1) {
			//there is a coma in line => it's a beatmap phase
			fout << line << "\n";
		}
		else {
			//No coma in line => to highscore line, break here
			break;
		}
	}

	//Save new highscore if it higher than previous highscore
	if (m_highscore < highscore) {
		m_highscore = highscore;
		m_rank = rank;
	}
	if (m_maxCombo < maxCombo) {
		m_maxCombo = maxCombo;
	}
	fout << m_highscore << "\n" << m_maxCombo << "\n" << m_rank;

	//Close file
	fout.close();
	fin.close();

	//Remove old file
	remove(file_name.c_str());
	//Rename new file to old file
	rename("temp.txt", file_name.c_str());
}

std::string Song::GetPath()
{
	return m_songPath;
}
