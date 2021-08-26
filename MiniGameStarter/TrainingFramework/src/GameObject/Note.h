#pragma once
#include "Area2D.h"
#include "Sprite2D.h"
class Note
	: public Area2D
{
private:
	std::shared_ptr<Sprite2D> m_sprite;
public:

	void Update(float deltaTime) override;
	void Draw() override;
};

