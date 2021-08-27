#pragma once
#include "Area2D.h"
#include "Sprite2D.h"
class Note
	: public Area2D
{
private:
	float m_speed;
	const float M_SPAWN_Y;
	float m_finish_y;
	float m_bpm;
	int m_difficulty;
	std::vector<Sprite2D*> m_listSprite;
public:
	Note() :m_speed(0), M_SPAWN_Y(0), m_finish_y(Globals::screenHeight), m_bpm(0), m_difficulty(4) {};
	Note(float finish_y, float bpm, int difficulty, Point2D position);
	~Note();
	void Update(float deltaTime) override;
	void Draw() override;
};

