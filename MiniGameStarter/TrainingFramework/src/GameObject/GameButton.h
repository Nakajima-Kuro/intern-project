#pragma once 
#include "Sprite2D.h"

class SoundServer;

class GameButton : public Sprite2D
{
public:
	GameButton() : Sprite2D(), m_pBtClick(nullptr), m_isHolding(false) {}
	GameButton(std::shared_ptr<Model> model, std::shared_ptr<Shader> shader, std::shared_ptr<Texture> texture);
	~GameButton();
	void	SetOnClick(void	(*pBtClick)());
	void	SetClickSfx(std::string name);
	bool	HandleTouchEvents(GLint x, GLint y, bool bIsPressed);
	bool	IsHolding();

private:
	void	(*m_pBtClick)();
	bool	m_isHolding;
	std::shared_ptr<SoundServer> m_clickingSfx;
};
