#include "GSPlay.h"
#include "GSIntro.h"
#include "GSMenu.h"
#include "GSCredit.h"
#include "GSPause.h"
#include "GSLibrary.h"

#include "GameStatebase.h"

GameStateBase::GameStateBase(StateType stateType) : m_stateType(stateType), m_keyPressed(0)
{}

std::shared_ptr<GameStateBase> GameStateBase::CreateState(StateType stt)
{
	std::shared_ptr<GameStateBase> gs = nullptr;
	switch (stt)
	{
	case StateType::STATE_INVALID:
		break;
	case StateType::STATE_INTRO:
		gs = std::make_shared<GSIntro>();
		break;
	case StateType::STATE_MENU:
		gs = std::make_shared<GSMenu>();
		break;
	case StateType::STATE_LIBRARY:
		gs = std::make_shared<GSLibrary>();
		break;
	case StateType::STATE_PLAY:
		gs = std::make_shared<GSPlay>();
		break;
	case StateType::STATE_PAUSE:
		gs = std::make_shared<GSPause>();
		break;
	case StateType::STATE_CREDIT:
		gs = std::make_shared<GSCredit>();
		break;
	default:
		break;
	}
	return gs;
}

StateType GameStateBase::GetGameStateType()
{
	return m_stateType;
}