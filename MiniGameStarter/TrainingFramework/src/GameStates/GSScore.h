#pragma once
#include "GameStateBase.h"
class GameButton;
class SongButton;
class GSScore :
	public GameStateBase
{
public:
	GSScore();
	~GSScore();

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
	std::shared_ptr<Sprite2D> m_background;
	std::shared_ptr<SongButton> m_songTitle;
	std::list<std::shared_ptr<Text>> m_listText;
	std::list<std::shared_ptr<GameButton>> m_listButton;

	GLfloat m_marginLeft = 120;
};

