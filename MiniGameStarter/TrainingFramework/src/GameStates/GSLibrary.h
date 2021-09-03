#pragma once
#include "GameStateBase.h"
class SongButton;
class TweeningSprite2D;
class GameButton;

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

	void	UpdateButtonInfo();

private:
	std::shared_ptr<Sprite2D>					m_background;
	std::shared_ptr<Text>						m_title;
	std::shared_ptr<GameButton>					m_backButton;

	std::vector<std::shared_ptr<Song>>			m_library;
	std::vector<std::shared_ptr<SongButton>>	m_listButton;
	std::vector<std::shared_ptr<Sprite2D>>		m_listForeground;
	std::shared_ptr<TweeningSprite2D>			m_arrow;
	int m_position;
};

