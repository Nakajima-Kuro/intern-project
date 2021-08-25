#pragma once
#include "GameStateBase.h"
#include "Conductor.h"

class Sprite2D;
class Sprite3D;
class Text;
class GameButton;

class GSPlay :
	public GameStateBase
{
public:
	GSPlay();
	~GSPlay();

	void	Init() override;
	void	Exit() override;

	void	Pause() override;
	void	Resume() override;

	void	HandleEvents() override;
	void	HandleKeyEvents(int key, bool bIsPressed) override;
	void	HandleTouchEvents(int x, int y, bool bIsPressed) override;
	void	HandleMouseMoveEvents(int x, int y) override;
	void	Update(float deltaTime) override;
	void	Draw() override;

private:
	//int m_score_value;
	//int combo_value;
	std::shared_ptr<Sprite2D>	m_background;
	std::shared_ptr<Text>		m_score;
	std::shared_ptr<Text>		m_scoreTitle;
	std::shared_ptr<Text>		m_combo;
	std::shared_ptr<Text>		m_comboTitle;

	//ArrowButton
	std::list<std::shared_ptr<ArrowButton>> m_listArrowButton;
	std::shared_ptr<GameButton>	m_backButton;
	const GLint m_arrowButtonY = Globals::screenHeight - 70;

	//Conductor
	Conductor* conductor;
};