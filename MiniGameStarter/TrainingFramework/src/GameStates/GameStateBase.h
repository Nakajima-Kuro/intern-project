#pragma once
#include "GameStateMachine.h"
#include "GameManager/ResourceManagers.h"


class GameStateBase
{
public:
	GameStateBase() : m_stateType(StateType::STATE_INVALID), m_keyPressed(0), m_score(0), m_perfect(0), m_good(0), m_okay(0), m_maxCombo(0), m_combo(0) {}
	GameStateBase(StateType stateType);
	virtual ~GameStateBase() {}

	virtual void Init() = 0;
	virtual void Exit() = 0;

	virtual void Pause() = 0;
	virtual void Resume() = 0;

	virtual void HandleEvents() = 0;
	virtual void HandleKeyEvents(int key, bool bIsPressed) = 0;
	virtual void HandleTouchEvents(int x, int y, bool bIsPressed) = 0;
	virtual void HandleMouseMoveEvents(int x, int y) = 0;
	virtual void Update(float deltaTime) = 0;
	virtual void Draw() = 0;

	static std::shared_ptr<GameStateBase> CreateState(StateType stt);
	StateType GetGameStateType();

protected:
	//Handle all the score and combo
	int m_score;
	int m_perfect;
	int m_good;
	int m_okay;
	int m_maxCombo;
	int m_combo;
	//Song name to load
	std::string m_songName = "Myths You Forgot (feat. Toby Fox)";

	int m_keyPressed;
	StateType m_stateType;
};

