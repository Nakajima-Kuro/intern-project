#pragma once
#include "GameStateBase.h"
#include "IObserver.h"

class Sprite2D;
class Area2D;
class Text;
class GameButton;
class ArrowButton;
class Note;
class NotePool;
class Conductor;

class GSPlay :
	public GameStateBase, public IObserver
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

	//Signal Handling
	void	Update(const std::string& message_from_subject);

private:
	std::shared_ptr<Sprite2D>	m_background;
	std::shared_ptr<Text>		m_textScore;
	std::shared_ptr<Text>		m_textCombo;
	std::shared_ptr<Text>		m_textComboValue;

	//Handle all the score and combo
	unsigned int m_score;
	int m_perfect;
	int m_good;
	int m_okay;
	int m_miss;
	int m_maxCombo;
	int m_combo;

	//ArrowButton
	const GLint m_arrowButtonY = Globals::screenHeight - 70;
	std::vector<std::shared_ptr<ArrowButton>> m_listArrowButton;

	int m_currentMapPosition;	//current position in the map
	std::shared_ptr<Song> m_song;//All info about the song
	Conductor* m_conductor;
	std::vector<std::vector<int>> m_beatMap;

	//List of note
	NotePool* m_notePool;
	std::list<std::shared_ptr<Area2D>> m_listNoteArea;

	//Others button
	std::shared_ptr<GameButton>	m_backButton;

	Vector2 GetSpawnPosition(int position);
	void IncreaseScore(int score);
	void getCurrentMapPosition(int beat);
};