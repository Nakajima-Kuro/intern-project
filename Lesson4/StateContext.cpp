#include "StateContext.h"

StateContext::StateContext(State* state)
{
	this->m_currentState = state;
	m_currentState->setContext(this);
}

StateContext::~StateContext()
{
	delete m_currentState;
}

void StateContext::start()
{
	m_currentState->start();
}

void StateContext::changeState(State* state)
{
	//Delete old state
	if (m_currentState != nullptr) {
		delete m_currentState;
	}
	//Transit to new state
	m_currentState = state;
	m_currentState->setContext(this);
	m_currentState->start();
}
