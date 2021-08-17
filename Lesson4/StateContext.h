#pragma once
#include<iostream>
#include"State.h"
class StateContext
{
private:
	State* m_currentState;
public:
	StateContext(State* state);
	virtual ~StateContext();
	void start();
	void changeState(State* state);
};

