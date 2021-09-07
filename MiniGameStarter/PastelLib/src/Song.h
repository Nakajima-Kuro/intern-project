#pragma once
#include <vector>
#include <string>
class Song
{
public:
	Song(std::string songPath);
	~Song();
	void Init();

	std::string GetName();
	float GetBpm();
	int GetMeasures();
	int GetDifficulty();
	int GetBeatOffset();
	std::vector<std::vector<int>> GetBeatMap();

	int GetHighScore();
	int GetMaxCombo();
	std::string GetRank();
	void SaveHighScore(int highscore, int maxCombo, std::string rank);

	std::string GetPath();
private:
	std::string m_name;//Name of the song, not file name
	float m_bpm;
	int m_measures;
	int m_difficulty;
	int m_beatOffset;
	std::vector<std::vector<int>> m_beatMap;

	int m_highscore;
	int m_maxCombo;
	std::string m_rank;

	std::string m_songPath;
};

