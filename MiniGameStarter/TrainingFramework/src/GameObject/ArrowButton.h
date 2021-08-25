#pragma once
#include "Sprite2D.h"
class ArrowButton :
	public Sprite2D
{
public:
	ArrowButton() : Sprite2D(), m_listTexture({ NULL, NULL }), m_input(-1) {}
	ArrowButton(std::shared_ptr<Model> model, std::shared_ptr<Shader> shader, std::pair<std::shared_ptr<Texture>, std::shared_ptr<Texture>> textureStatus, int input);
	std::pair<std::shared_ptr<Texture>, std::shared_ptr<Texture>> m_listTexture;
	int HandleKeyEvents(int key, bool bIsPressed);
private:
	int m_input;
};

