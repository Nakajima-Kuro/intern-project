#pragma once
#include "Area2D.h"
#include "Sprite2D.h"
class Note
	: public Area2D
{
private:
	Vector2 m_spawnLocation;
	Vector2 m_finishLocation;
	float m_speed;
	float m_bpm;
	int m_difficulty;
	AnimationSprite2D* m_sprite;
public:
	Note() : m_spawnLocation(Vector2()), m_finishLocation(Vector2()), m_speed(0), m_bpm(0), m_difficulty(4) {};
	Note(Vector2 spawnPosition, Vector2 finishPosition, float bpm, int difficulty);
	~Note();
	void Update(float deltaTime) override;
	void Draw() override;
};

