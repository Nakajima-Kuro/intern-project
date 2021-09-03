#include "GameButton.h"
#include "SoundServer.h"
#include "ResourceManagers.h"

GameButton::GameButton(std::shared_ptr<Model> model, std::shared_ptr<Shader> shader, std::shared_ptr<Texture> texture)
	: Sprite2D(-1, model, shader, texture), m_pBtClick(nullptr), m_isHolding(false)
{
}

GameButton::~GameButton()
{
}

void GameButton::SetOnClick(void(*pBtClickFun)())
{
	m_pBtClick = pBtClickFun;
}

void GameButton::SetClickSfx(std::string name)
{
	m_clickingSfx = ResourceManagers::GetInstance()->GetSfx(name);
}

bool GameButton::HandleTouchEvents(GLint x, GLint y, bool bIsPressed)
{
	bool isHandled = false;
	if (bIsPressed)
	{
		if ((x > m_position.x - m_iWidth / 2) && (x < m_position.x + m_iWidth / 2)
			&& (y > m_position.y - m_iHeight / 2) && (y < m_position.y + m_iHeight / 2))
		{
			// The button is being pressed down
			m_isHolding = true;
		}
	}
	else
	{
		if ((x > m_position.x - m_iWidth / 2) && (x < m_position.x + m_iWidth / 2)
			&& (y > m_position.y - m_iHeight / 2) && (y < m_position.y + m_iHeight / 2)
			&& m_isHolding == true)
		{
			// Only perform click action when the same button was pressed down and released
			if (m_clickingSfx != nullptr) {
				m_clickingSfx->Play();
			}
			m_pBtClick();
			isHandled = true;
		}
		m_isHolding = false;
	}
	return isHandled;
}

bool GameButton::IsHolding()
{
	return m_isHolding;
}
