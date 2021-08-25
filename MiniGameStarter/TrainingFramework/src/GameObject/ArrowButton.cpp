#include "ArrowButton.h"
ArrowButton::ArrowButton(std::shared_ptr<Model> model, std::shared_ptr<Shader> shader, std::pair<std::shared_ptr<Texture>, std::shared_ptr<Texture>> listTexture, int input)
	: Sprite2D(-1, model, shader, listTexture.first), m_listTexture(listTexture), m_input(input)
{
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
