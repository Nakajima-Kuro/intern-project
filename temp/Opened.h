#pragma once
#include<iostream>
#include "StateContext.h"
#include"State.h"
class Opened : public State
{
public:
	void close(StateContext* context) override;
	void handleInput(StateContext* context, char* input) override;
	void logState() override;
};

class Closed;