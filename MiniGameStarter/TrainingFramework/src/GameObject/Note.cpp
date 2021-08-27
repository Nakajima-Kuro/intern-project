#include "Note.h"
#include "ResourceManagers.h"

Note::Note(float finish_y, float bpm, int difficulty, Point2D position)
	:m_speed(0), M_SPAWN_Y(0), m_finish_y(Globals::screenHeight), m_bpm(0), m_difficulty(4)
{
	//Init 3 arrow sprite
	auto model = ResourceManagers::GetInstance()->GetModel("Sprite2D.nfg");
	auto shader = ResourceManagers::GetInstance()->GetShader("TextureShader");

	auto texture = ResourceManagers::GetInstance()->GetTexture("Arrow/Left/arrow_button_left_3.tga");
	

	//Set note position
	this->SetPosition(position);
}

Note::~Note()
{
	for (auto& element : m_listSprite) {
		delete element;
	}
	m_listSprite.clear();
}

void Note::Update(float deltaTime)
{
	this->SetPosition(this->GetPosition().GetX(), this->GetPosition().GetY() + m_speed * deltaTime);
	Area2D::Update(deltaTime);
}

void Note::Draw()
{
	Area2D::Draw();
}
