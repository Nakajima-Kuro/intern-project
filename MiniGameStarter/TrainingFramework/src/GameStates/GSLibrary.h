#pragma once
#include "GameStateBase.h"
class GSLibrary :
    public GameStateBase
{
public:
    GSLibrary();
    ~GSLibrary();

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
	std::vector<std::shared_ptr<Song>> m_library;
	std::shared_ptr<Sprite2D>				m_background;
	//std::list<std::shared_ptr<GameButton>>	m_listButton;
	int m_position;
};

