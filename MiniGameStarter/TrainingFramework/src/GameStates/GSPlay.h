#pragma once
#include "GameStateBase.h"
#include "IObserver.h"

class Sprite2D;
class Area2D;
class Text;
class GameButton;
class Conductor;
class ArrowButton;
class Note;
class NotePool;

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

	//ArrowButton
	const GLint m_arrowButtonY = Globals::screenHeight - 70;
	std::vector<std::shared_ptr<ArrowButton>> m_listArrowButton;

	//Data of the beat map
	//Beat map will look like this:
	//[the beat when counter advance to next phase of the beat map, measure 1, measure 2, measure 3,...]
	int m_currentMapPosition;	//current position in the map
	std::vector<std::vector<int>> m_beatMap;

	//List of note
	NotePool* m_notePool;
	std::list<std::shared_ptr<Area2D>> m_listNote;

	//Conductor
	Conductor* m_conductor;

	//Others button
	std::shared_ptr<GameButton>	m_backButton;
	std::shared_ptr<Note> m_note;

	Vector2 GetSpawnPosition(int position);
	void IncreaseScore(int score);
};