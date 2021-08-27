#pragma once
#include "Area2D.h"

class AnimationSprite2D;

class Note
	: public Area2D
{
private:
	AnimationSprite2D* m_sprite;
	Vector2 m_spawnLocation;
	Vector2 m_finishLocation;
	float m_speed;
	float m_bpm;
	int m_difficulty;
public:
	Note();
	Note(Vector2 spawnPosition, Vector2 finishPosition, float bpm, int difficulty);
	~Note();

	//Game function
	void Init();
	void Update(float deltaTime) override;
	void Draw() override;

	void SetLane(int lane);
	void Destroy(std::string status);
};

