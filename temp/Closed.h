#pragma once
#include<iostream>
#include "StateContext.h"
#include "State.h"
class Closed :
	public State
{
public:
	void lock(StateContext* context) override;
	void open(StateContext* context) override;
	void handleInput(StateContext* context, char* input) override;
	void logState() override;
};

class Locked;
class Opened;