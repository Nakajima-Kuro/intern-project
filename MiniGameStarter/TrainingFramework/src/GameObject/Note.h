#pragma once
#include "Area2D.h"

class AnimationSprite2D;
class Text;

class Note
	: public Area2D
{
public:
	Note();
	Note(Vector2 spawnPosition, Vector2 finishPosition, float bpm, int difficulty);
	~Note();

	//Game function
	void Init();
	void Update(float deltaTime) override;
	void Draw() override;

	void SetSize(GLint sizeX, GLint sizeY);
	void Set2DPosition(Vector2 position);
	void Set2DPosition(GLint x, GLint y);
	void SetFinishPosition(Vector2 position);
	void SetFinishPosition(GLint x, GLint y);
	void SetActive(bool isActive);
	bool IsActive();

	void SetLane(int lane);
	void Destroy(std::string status);

private:
	AnimationSprite2D* m_sprite;
	Text* m_text;
	Vector2 m_spawnPosition;
	Vector2 m_finishPosition;
	float m_speed;
	float m_bpm;
	int m_difficulty;
	bool m_isActive;

	void CalculateSpeed();
};

