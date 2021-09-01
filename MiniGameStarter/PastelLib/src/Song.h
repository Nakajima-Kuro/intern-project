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
	std::string GetPath();
private:
	std::string m_name;//Name of the song, not file name
	float m_bpm;
	int m_measures;
	int m_difficulty;
	int m_beatOffset;
	std::vector<std::vector<int>> m_beatMap;

	std::string m_songPath;
};

