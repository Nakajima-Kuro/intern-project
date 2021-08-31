#pragma once
#include <vector>
class Conductor;

class Song
{
public:
	float GetBpm();
	void SetBpm(float bpm);
	int GetMeasures();
	void SetMeasures(int measures);
	int GetDifficulty();
	void SetDifficulty(int difficulty);
	int GetBeatOffset();
	void SetBeatOffset(int beatOffset);

	Conductor* GetConductor();
	void SetConductor(Conductor* conductor);
	std::vector<std::vector<int>> GetBeatMap();
	void SetBeatMap(std::vector<std::vector<int>> beatMap);
private:
	float m_bpm;
	int m_measures;
	int m_difficulty;
	int m_beatOffset;
	Conductor* m_conductor;
	std::vector<std::vector<int>> m_beatMap;
};

