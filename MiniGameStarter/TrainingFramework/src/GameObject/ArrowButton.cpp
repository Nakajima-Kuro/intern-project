#include "ArrowButton.h"
ArrowButton::ArrowButton(std::shared_ptr<Model> model, std::shared_ptr<Shader> shader, std::pair<std::shared_ptr<Texture>, std::shared_ptr<Texture>> listTexture, int input)
	: Sprite2D(-1, model, shader, listTexture.first), m_listTexture(listTexture), m_input(input)
{
	m_areaPerfect = std::make_shared<Area2D>(Point2D(0, 0), 16, 16, "perfect");
	m_areaGood = std::make_shared<Area2D>(Point2D(0, 0), 16, 32, "good");
	m_areaOkay = std::make_shared<Area2D>(Point2D(0, 0), 16, 48, "okay");
}

int ArrowButton::HandleKeyEvents(int key, bool bIsPressed)
{
	if (key == m_input) {
		if (bIsPressed)
		{
			// The button is being pressed down
			this->SetTexture(m_listTexture.second);
		}
		else
		{
			this->SetTexture(m_listTexture.first);
		}
	}
	return 0;
}

void ArrowButton::Update(const std::string& message_from_subject)
{
	//Handle all 6 message here
}

void ArrowButton::Update(float deltaTime)
{
	m_areaPerfect->SetPosition(m_position.x, m_position.y);
	m_areaGood->SetPosition(m_position.x, m_position.y);
	m_areaOkay->SetPosition(m_position.x, m_position.y);
	m_areaPerfect->Update(deltaTime);
	m_areaGood->Update(deltaTime);
	m_areaOkay->Update(deltaTime);
}

void ArrowButton::Draw()
{
	Sprite2D::Draw();
	m_areaGood->Draw();
	m_areaOkay->Draw();
	m_areaPerfect->Draw();
}
