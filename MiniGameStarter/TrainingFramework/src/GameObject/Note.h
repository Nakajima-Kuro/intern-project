#pragma once
#include "Area2D.h"
#include "Sprite2D.h"
class Note
	: public Area2D
{
private:
	float m_speed;
	float m_spawn_y;
	float m_finish_y;
	float m_bpm;
	int m_difficulty;
	std::vector<Sprite2D*> m_listSprite;
public:
	Note() :m_speed(0), m_spawn_y(0), m_finish_y(Globals::screenHeight), m_bpm(0), m_difficulty(4) {};
	Note(Vector2 spawnPosition, Vector2 finishPosition, float bpm, int difficulty);
	~Note();
	void Update(float deltaTime) override;
	void Draw() override;
};

