#include "ArrowButton.h"
ArrowButton::ArrowButton(std::shared_ptr<Model> model, std::shared_ptr<Shader> shader, std::pair<std::shared_ptr<Texture>, std::shared_ptr<Texture>> listTexture, int input)
	: Sprite2D(-1, model, shader, listTexture.first), m_listTexture(listTexture), m_isHolding(false), m_input(input)
{
}

int ArrowButton::HandleKeyEvents(int key, bool bIsPressed)
{
	if (bIsPressed && key == m_input)
	{
		// The button is being pressed down
		m_isHolding = true;
		this->SetTexture(m_listTexture.second);
	}
	else
	{
		if (m_isHolding == true)
		{
			this->SetTexture(m_listTexture.first);
			m_isHolding = false;
		}
		
	}
	return 0;
}
