#pragma once
#include<iostream>
class StateContext;
class State
{
public:
	void setContext(StateContext* context);
	virtual void start() = 0;
	virtual void handleInput() = 0;
	void clrscr();
protected:
	StateContext* m_context = nullptr;
};
