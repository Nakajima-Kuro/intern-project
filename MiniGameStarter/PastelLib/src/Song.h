#pragma once
#include <vector>
#include <string>
class Conductor;

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

	Conductor* GetConductor();
	std::vector<std::vector<int>> GetBeatMap();
private:
	std::string m_name;
	float m_bpm;
	int m_measures;
	int m_difficulty;
	int m_beatOffset;
	Conductor* m_conductor;
	std::vector<std::vector<int>> m_beatMap;

	std::string m_songPath;
};

